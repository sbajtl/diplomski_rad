#include "Extractor.h"

Extractor::Extractor()
: m_extractor(new DocumentExtractor)
{}

Extractor::~Extractor() = default;

const MrzZoneStruct* Extractor::detectMrzZone(unsigned char* position, int width,int height){
  static MrzZoneStruct* output;
  output = m_extractor->detectMrz(position, width, height);
  return output;
}
