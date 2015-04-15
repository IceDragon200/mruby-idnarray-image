#include "idnarray_image.hxx"

NArrayImage::NArrayImage()
{
  w = 0;
  h = 0;
  data = NULL;
  stride = 0;
}

NArrayImage::NArrayImage(int _w, int _h, NArray *_data)
{
  w = _w;
  h = _h;
  data = _data;
  stride = w * data->element_size;
}

NArrayImage::~NArrayImage()
{
  data = NULL; // data is handled externally clean it up yourself.
}

bool
NArrayImage::InBounds(int x, int y)
{
  if (x < 0 || w < x || y < 0 || h < y) {
    return false;
  }
  return true;
}

struct NArrayImagePixel
NArrayImage::GetPixel(int x, int y)
{
  if (!InBounds(x, y)) return NArrayImagePixel(0);
  uint8_t *ptr = &((uint8_t*)data->data)[x + y * stride];
  /* NOTE: I wonder if I should just increment and set instead */
  return NArrayImagePixel(ptr[0], ptr[1], ptr[2], ptr[3]);
}

void
NArrayImage::SetPixel(int x, int y, struct NArrayImagePixel pixel)
{
  if (!InBounds(x, y)) return;
  uint8_t *ptr = &((uint8_t*)data->data)[x + y * stride];
  uint8_t *v = pixel.values;
  *ptr++ = *v++;
  *ptr++ = *v++;
  *ptr++ = *v++;
  *ptr = *v;
}
