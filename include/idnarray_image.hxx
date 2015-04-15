#ifndef IDNARRAY_IMAGE_H
#define IDNARRAY_IMAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "idnarray.hxx"

struct NArrayImagePixel {
  union {
    struct {
      uint8_t r, g, b, a;
    };
    uint8_t values[4];
    uint32_t value;
  };

  NArrayImagePixel() { value = 0; };
  NArrayImagePixel(uint32_t _value) { value = _value; };
  NArrayImagePixel(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
  {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
  };
};

struct NArrayImage {
public:
  int w;
  int h;
  int stride;
  NArray *data;

  NArrayImage();
  NArrayImage(int _w, int _h, NArray *_data);
  ~NArrayImage();

  struct NArrayImagePixel GetPixel(int x, int y);
  void SetPixel(int x, int y, struct NArrayImagePixel pixel);
private:
  bool InBounds(int x, int y);
};

#endif
