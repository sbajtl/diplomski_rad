#ifndef EMSCRIPTEN_EXTRACTOR_H
#define EMSCRIPTEN_EXTRACTOR_H
#define EMSCRIPTEN 1

#include <memory>
#include <DocumentExtractor.h>

class Extractor
{
public:
  Extractor();
  virtual ~Extractor();
  virtual const MrzZoneStruct* detectMrzZone(unsigned char* position, int width,int height);
private:
    std::unique_ptr<DocumentExtractor> m_extractor;
};

#endif // EMSCRIPTEN_EXTRACTOR_H
