#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include "mrb/idnarray/image.hxx"

static struct RClass *narray_class;
static struct RClass *narray_image_class;

#define INTERNAL_NARRAY_IV_NAME() "__narray_inst__"
#define MRB_INTERNAL_NARRAY_IV_NAME() mrb_intern_cstr(mrb, INTERNAL_NARRAY_IV_NAME())

static void
narray_image_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    NArrayImage *img = (NArrayImage*)ptr;
    delete img;
  }
}

extern "C" const struct mrb_data_type mrb_idnarray_image_type = { "NArrayImage", narray_image_free };

static inline NArrayImage*
get_image(mrb_state *mrb, mrb_value self)
{
  return (NArrayImage*)mrb_data_get_ptr(mrb, self, &mrb_idnarray_image_type);
}

static inline NArray*
get_narray(mrb_state *mrb, mrb_value self)
{
  return (NArray*)mrb_data_get_ptr(mrb, self, &mrb_idnarray_type);
}

static mrb_value
narray_image_initialize(mrb_state *mrb, mrb_value self)
{
  NArray *narray;
  NArrayImage *image;
  mrb_value narray_value;
  mrb_int w;
  mrb_int h;
  int size;
  mrb_get_args(mrb, "ii", &w, &h);
  if (w <= 0 || h <= 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid width or height for Image");
  }
  size = (w * h) * (NArray::CalcContentTypeSize(NARRAY_UINT8) * 4);
  narray_value = mrb_narray_new(mrb, NARRAY_UINT8, size);
  /* need to keep a reference to the ruby NArray to avoid this being eaten,
     by the GC and causing the NArrayImage to spaz out */
  mrb_iv_set(mrb, self, MRB_INTERNAL_NARRAY_IV_NAME(), narray_value);
  narray = get_narray(mrb, narray_value);
  image = new NArrayImage(w, h, narray);
  mrb_data_init(self, image, &mrb_idnarray_image_type);
  return self;
}

static mrb_value
narray_image_get_narray(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, MRB_INTERNAL_NARRAY_IV_NAME());
}

static mrb_value
narray_image_get_pixel(mrb_state *mrb, mrb_value self)
{
  NArrayImage *img;
  mrb_value ary;
  mrb_int x, y;
  NArrayImagePixel px;
  mrb_get_args(mrb, "ii", &x, &y);
  img = get_image(mrb, self);
  px = img->GetPixel(x, y);
  ary = mrb_ary_new_capa(mrb, 4);
  mrb_ary_push(mrb, ary, mrb_fixnum_value(px.values[0]));
  mrb_ary_push(mrb, ary, mrb_fixnum_value(px.values[1]));
  mrb_ary_push(mrb, ary, mrb_fixnum_value(px.values[2]));
  mrb_ary_push(mrb, ary, mrb_fixnum_value(px.values[3]));
  return ary;
}

static mrb_value
narray_image_set_pixel(mrb_state *mrb, mrb_value self)
{
  NArrayImage *img;
  mrb_int x, y;
  mrb_int r, g, b, a;
  mrb_get_args(mrb, "iiiiii", &x, &y, &r, &g, &b, &a);
  img = get_image(mrb, self);
  img->SetPixel(x, y, NArrayImagePixel(r, g, b, a));
  return self;
}

extern "C" void
mrb_mruby_idnarray_image_gem_init(mrb_state *mrb)
{
  narray_class = mrb_class_get(mrb, "NArray");

  narray_image_class = mrb_define_class_under(mrb, narray_class, "Image", mrb->object_class);
  MRB_SET_INSTANCE_TT(narray_image_class, MRB_TT_DATA);

  mrb_define_method(mrb, narray_image_class, "initialize", narray_image_initialize, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, narray_image_class, "narray",     narray_image_get_narray, MRB_ARGS_NONE());
  mrb_define_method(mrb, narray_image_class, "get_pixel",  narray_image_get_pixel,  MRB_ARGS_REQ(2));
  mrb_define_method(mrb, narray_image_class, "set_pixel",  narray_image_set_pixel,  MRB_ARGS_REQ(6));
}

extern "C" void
mrb_mruby_idnarray_image_gem_final(mrb_state *mrb)
{
}
