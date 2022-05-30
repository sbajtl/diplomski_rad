#include <DocumentExtractor.h>
#include <opencv2/opencv.hpp>
#define SHOW_PROCESS_IMAGE 0

cv::Mat DocumentExtractor::getImage(uint8_t * position, int width, int height) {

  cv::Mat mat;

#if defined EMSCRIPTEN == 1
  mat = cv::Mat(height, width, CV_8UC4, position);
  //cv::cvtColor(mat, mat, cv::COLOR_RGBA2GRAY);
  //cv::cvtColor(mat, mat, cv::COLOR_GRAY2RGBA);
#else
  mat = cv::Mat(height, width, CV_8UC3, position);
  //cv::cvtColor(mat, mat, cv::COLOR_RGBA2GRAY);
#endif
  //cv::Mat roi = detect(mat, data);
  //detect(mat, data);
  auto zone = detectMrz(position, width, height);
  auto dataZone = cv::Rect(zone->x, zone->y, zone->width, zone->height);
  auto roi = mat(dataZone);
  return roi;
}

bool DocumentExtractor::detect(const cv::Mat &original) {
  // initialize a rectangular and square structuring kernel
  cv::Mat rectKernel = getStructuringElement(cv::MORPH_RECT, cv::Size(13, 5));
  cv::Mat sqKernel = getStructuringElement(cv::MORPH_RECT, cv::Size(21, 21));

  // resize the image and convert it to grayscale
  cv::Mat image;

  int scale_percent = 50;
  auto width = int(original.size().width * scale_percent / 100);
  auto height = int(original.size().height * scale_percent / 100);
  resize(original, image, cv::Size(width, height));
  cv::Mat gray;

#if defined EMSCRIPTEN == 1
  cv::cvtColor(image, gray, cv::COLOR_RGBA2GRAY);
  cv::cvtColor(gray, image, cv::COLOR_GRAY2RGBA);
#else
  cv::cvtColor(image, gray, cv::COLOR_RGBA2GRAY);
#endif

#if SHOW_PROCESS_IMAGE
  cv::imshow("Gray", gray);
#endif
  // smooth the image using a 3x3 Gaussian, then apply the blackhat
  // morphological operator to find dark regions on a light background
  cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);

#if SHOW_PROCESS_IMAGE
  cv::imshow("GaussianBlur", gray);
#endif

  cv::Mat blackhat;
  cv::morphologyEx(gray, blackhat, cv::MORPH_BLACKHAT, rectKernel);

#if SHOW_PROCESS_IMAGE
  cv::imshow("BlackHat", blackhat);
#endif

  // compute the Scharr gradient of the blackhat image and scale the
  // result into the range [0, 255]
  cv::Mat gradX;
  Sobel(blackhat, gradX, CV_32F, 1, 0, -1);
  gradX = abs(gradX);
  double minVal, maxVal;
  minMaxIdx(gradX, &minVal, &maxVal);
  cv::Mat gradXfloat = (255 * ((gradX - minVal) / (maxVal - minVal)));
  gradXfloat.convertTo(gradX, CV_8UC1);

#if SHOW_PROCESS_IMAGE
  cv::imshow("Scharr gradient", gradX);
#endif
  // apply a closing operation using the rectangular kernel to close
  // gaps in between letters -- then apply Otsu's thresholding method
  morphologyEx(gradX, gradX, cv::MORPH_CLOSE, rectKernel);
  cv::Mat thresh;
  threshold(gradX, thresh, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

#if SHOW_PROCESS_IMAGE
  cv::imshow("Horizontal closing", thresh);
#endif

  // perform another closing operation, this time using the square
  // kernel to close gaps between lines of the MRZ, then perform a
  // series of erosions to break apart connected components
  morphologyEx(thresh, thresh, cv::MORPH_CLOSE, sqKernel);
  cv::Mat nullKernel;
  erode(thresh, thresh, nullKernel, cv::Point(-1, -1), 4);

#if SHOW_PROCESS_IMAGE
  cv::imshow("Vertical closing", thresh);
#endif

  // during thresholding, it's possible that border pixels were
  // included in the thresholding, so let's set 5% of the left and
  // right borders to zero
  double p = image.size().height * 0.05;
  thresh = thresh(cv::Rect(p, p, image.size().width - 2 * p, image.size().height - 2 * p));

#if SHOW_PROCESS_IMAGE
  cv::imshow("Border removal", thresh);
#endif

  // find contours in the thresholded image and sort them by their
  // size
  std::vector<std::vector<cv::Point> > contours;
  findContours(thresh, contours, cv::RETR_EXTERNAL,
               cv::CHAIN_APPROX_SIMPLE);
  // Sort the contours in decreasing area
  sort(contours.begin(), contours.end(), [](const std::vector<cv::Point>& c1, const std::vector<cv::Point>& c2){
    return contourArea(c1, false) > contourArea(c2, false);
  });

  // Find the first contour with the right aspect ratio and a large width relative to the width of the image
  cv::Rect roiRect(0, 0, 0, 0);
  std::vector<std::vector<cv::Point> >::iterator border_iter = find_if(contours.begin(), contours.end(), [&roiRect, gray](std::vector<cv::Point> &contour) {
    // compute the bounding box of the contour and use the contour to
    // compute the aspect ratio and coverage ratio of the bounding box
    // width to the width of the image
    roiRect = boundingRect(contour);
    // dump_rect("Bounding rect", roiRect);
    // pprint([x, y, w, h])
    double aspect = (double) roiRect.size().width / (double) roiRect.size().height;
    double coverageWidth = (double) roiRect.size().width / (double) gray.size().height;
    // cerr << "aspect=" << aspect << "; coverageWidth=" << coverageWidth << endl;
    // check to see if the aspect ratio and coverage width are within
    // acceptable criteria
    if (aspect > 5 and coverageWidth > 0.5) {
      return true;
    }
    return false;
  });

  if (border_iter == contours.end()) {
    return false;
  }

  // Correct ROI for border removal offset
  roiRect += cv::Point(p, p);
  // pad the bounding box since we applied erosions and now need
  // to re-grow it
  int pX = (roiRect.x + roiRect.size().width) * 0.03;
  int pY = (roiRect.y + roiRect.size().height) * 0.03;
  roiRect -= cv::Point(pX, pY);
  roiRect += cv::Size(pX * 2, pY * 2);
  // Ensure ROI is within image
  roiRect &= cv::Rect(0, 0, image.size().width, image.size().height);
  // Make it relative to original image again
  float scale = static_cast<float>(original.size().width) / static_cast<float>(image.size().width);
  roiRect.x *= scale;
  roiRect.y *= scale;
  roiRect.width *= scale;
  roiRect.height *= scale;

  auto detectedZone = new MrzZoneStruct();
  detectedZone->x = roiRect.x;
  detectedZone->y = roiRect.y;
  detectedZone->width = roiRect.width;
  detectedZone->height = roiRect.height;
  this->setDetectedZone(*detectedZone);
  delete(detectedZone);

  return true;
}

MrzZoneStruct *DocumentExtractor::detectMrz(uint8_t *position, int width, int height) {
  cv::Mat mat;
#if defined EMSCRIPTEN == 1
  mat = cv::Mat(height, width, CV_8UC4, position);
#else
  mat = cv::Mat(height, width, CV_8UC3, position);
#endif
  this->detect(mat);

  return const_cast<MrzZoneStruct *>(&getDetectedZone());
}

void DocumentExtractor::setDetectedZone(const MrzZoneStruct &detectedZone) {
  DocumentExtractor::detectedZone = detectedZone;
}

const MrzZoneStruct &DocumentExtractor::getDetectedZone() const {
  return detectedZone;
}

