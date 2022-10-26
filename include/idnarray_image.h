#ifndef IDNARRAY_IMAGE_H
#define IDNARRAY_IMAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "idnarray.h"

struct NArrayImagePixel {
  union {
    struct {
      uint8_t r, g, b, a;
    };
    uint8_t values[4];
    uint32_t value;
  };
};

struct NArrayImage {
  int w;
  int h;
  int stride;
  struct NArray *data;
};

int idnarray_image_init(struct NArrayImage *image);
int idnarray_image_init_with_narray(struct NArrayImage *image, size_t w, size_t h, struct NArray *narray);
struct NArrayImagePixel idnarray_image_get_pixel(struct NArrayImage *image, size_t x, size_t y);
int idnarray_image_set_pixel(struct NArrayImage *image, size_t x, size_t y, struct NArrayImagePixel pixel);
bool idnarray_image_in_bounds(struct NArrayImage *image, size_t x, size_t y);

#endif
