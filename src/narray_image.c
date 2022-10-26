#include "idnarray_image.h"

int
idnarray_image_init(struct NArrayImage *image)
{
  image->w = 0;
  image->h = 0;
  image->stride = 0;
  image->data = NULL;
  return IDNARRAY_OK;
}

int
idnarray_image_init_with_narray(struct NArrayImage *image, size_t w, size_t h, struct NArray *narray)
{
  image->w = w;
  image->h = h;
  image->data = narray;
  image->stride = image->w * image->data->element_size;
  return IDNARRAY_OK;
}

bool
idnarray_image_in_bounds(struct NArrayImage *image, size_t x, size_t y)
{
  if (image->w <= x || image->h <= y) {
    return false;
  }
  return true;
}

struct NArrayImagePixel
idnarray_image_get_pixel(struct NArrayImage *image, size_t x, size_t y)
{
  struct NArrayImagePixel pixel;
  pixel.value = 0;

  if (!idnarray_image_in_bounds(image, x, y)) {
    return pixel;
  }

  uint8_t *ptr = &((uint8_t*)image->data->data)[x + y * image->stride];

  /* NOTE: I wonder if I should just increment and set instead */
  pixel.values[0] = ptr[0];
  pixel.values[1] = ptr[1];
  pixel.values[2] = ptr[2];
  pixel.values[3] = ptr[3];

  return pixel;
}

int
idnarray_image_set_pixel(struct NArrayImage *image, size_t x, size_t y, struct NArrayImagePixel pixel)
{
  if (!idnarray_image_in_bounds(image, x, y)) {
    return IDNARRAY_SOURCE_OUT_OF_RANGE;
  }

  uint8_t *ptr = &((uint8_t*)image->data->data)[x + y * image->stride];
  uint8_t *v = pixel.values;
  *ptr++ = *v++;
  *ptr++ = *v++;
  *ptr++ = *v++;
  *ptr = *v;

  return IDNARRAY_OK;
}
