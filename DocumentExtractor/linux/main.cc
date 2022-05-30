#include <iostream>
#include <DocumentExtractor.h>
#include <opencv2/opencv.hpp>
#include <chrono>

#define WORK_WITH_IMAGE 0

using namespace std::chrono;
typedef std::chrono::duration<float> float_seconds;


//-----------------------------------------------------------------------------

int main()
{
  MrzZoneStruct *detectedMrz;
  cv::Mat image;
  cv::Rect2i roiRect;
  uint8_t *position;

  if (!WORK_WITH_IMAGE)
  {
    cv::VideoCapture capture;
    cv::Mat frame;
    capture.open(0);

    if (capture.isOpened())
    {
      capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
      capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
      // Capture frames from video and detect faces
      std::cout << "Detection Started...." << std::endl;
      while (1)
      {
        capture >> frame;
        if (frame.empty())
          break;

        auto start = high_resolution_clock::now();
        image = frame.clone();
        position = image.data;

        auto *documentExtractor = new DocumentExtractor();
        detectedMrz = documentExtractor->detectMrz(position, image.size().width, image.size().height);
        roiRect = cv::Rect(detectedMrz->x, detectedMrz->y, detectedMrz->width, detectedMrz->height);
        cv::rectangle(image, roiRect, cv::Scalar(0, 255, 0), 2);

        auto stop = high_resolution_clock::now();
        // Subtract stop and start timepoints and
        // cast it to required unit. Predefined units
        // are nanoseconds, microseconds, milliseconds,
        // seconds, minutes, hours. Use duration_cast()
        // function.
        auto duration = duration_cast<float_seconds>(stop - start);
        // To get the value of duration use the count()
        // member function on the duration object
        std::cout <<  1000 / (duration.count() * 1000) << std::endl;
        cv::putText(image, std::to_string(1000 / (duration.count() * 1000)), cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

        imshow("Mrz Detection", image);
        delete documentExtractor;


        char c = (char) cv::waitKey(10);

        // Press q to exit from window
        if (c == 27 || c == 'q' || c == 'Q')
          break;
      }
    } else
    {
      std::cout << "Could not Open Camera";
    }
  } else
  {
    image = cv::imread("/Users/sasabajtl/CLionProjects/DocumentExtractor/linux/mrz.png");
    position = image.data;
    try
    {
      auto *documentExtractor = new DocumentExtractor();
      detectedMrz = documentExtractor->detectMrz(position, image.size().width, image.size().height);
      roiRect = cv::Rect(detectedMrz->x, detectedMrz->y, detectedMrz->width, detectedMrz->height);

      cv::rectangle(image, roiRect, cv::Scalar(0, 255, 0), 2);
      imshow("MRZ Detection", image);
      cv::waitKey(0);
      image.release();
      delete (documentExtractor);
    }
    catch (const std::exception &ex)
    {
      std::cout << "Error occurred: " << ex.what() << std::endl;
    }
  }

  return 0;
}