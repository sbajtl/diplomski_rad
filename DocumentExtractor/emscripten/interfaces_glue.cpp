
#include <emscripten.h>

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.

EM_JS(void, array_bounds_check_error, (size_t idx, size_t size), {
  throw 'Array index ' + idx + ' out of bounds: [0,' + size + ')';
});

void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    array_bounds_check_error(array_idx, array_size);
  }
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// MrzZoneStruct

MrzZoneStruct* EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_MrzZoneStruct_4(int x, int y, int width, int height) {
  return new MrzZoneStruct(x, y, width, height);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_get_x_0(MrzZoneStruct* self) {
  return self->x;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_set_x_1(MrzZoneStruct* self, int arg0) {
  self->x = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_get_y_0(MrzZoneStruct* self) {
  return self->y;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_set_y_1(MrzZoneStruct* self, int arg0) {
  self->y = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_get_width_0(MrzZoneStruct* self) {
  return self->width;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_set_width_1(MrzZoneStruct* self, int arg0) {
  self->width = arg0;
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_get_height_0(MrzZoneStruct* self) {
  return self->height;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct_set_height_1(MrzZoneStruct* self, int arg0) {
  self->height = arg0;
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_MrzZoneStruct___destroy___0(MrzZoneStruct* self) {
  delete self;
}

// Extractor

Extractor* EMSCRIPTEN_KEEPALIVE emscripten_bind_Extractor_Extractor_0() {
  return new Extractor();
}

const MrzZoneStruct* EMSCRIPTEN_KEEPALIVE emscripten_bind_Extractor_detectMrzZone_3(Extractor* self, unsigned char* position, int width, int height) {
  return self->detectMrzZone(position, width, height);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Extractor___destroy___0(Extractor* self) {
  delete self;
}

}

