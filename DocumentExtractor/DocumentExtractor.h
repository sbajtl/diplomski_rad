#ifndef DOCUMENT_EXTRACTOR_H
#define DOCUMENT_EXTRACTOR_H

#include <string>
#include <opencv2/core/mat.hpp>

struct MrzZoneStruct {
  MrzZoneStruct() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
  }

  MrzZoneStruct(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  int x;
  int y;
  int width;
  int height;
};

class DocumentExtractor {
public:
  DocumentExtractor() = default;
  ~DocumentExtractor() = default;

  cv::Mat getImage(uint8_t * position, int width, int height);
  MrzZoneStruct *detectMrz(uint8_t * position, int width, int height);

  [[nodiscard]] const MrzZoneStruct &getDetectedZone() const;
  void setDetectedZone(const MrzZoneStruct &detectedZone);

private:
  MrzZoneStruct detectedZone;
  bool detect(const cv::Mat &original);
};
#endif // DOCUMENT_EXTRACTOR_H