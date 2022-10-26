mruby-idnarray-image
====================

An Image class using NArray. All `Image`s are RGBA32 (8bits per channel).

## mrb_config.rb
```ruby
MRuby::Build.new do |conf|
  # ...
  conf.gem '/home/icy/docs/codes/IceDragon/mruby-gems/mruby-idnarray'
  conf.gem '/home/icy/docs/codes/IceDragon/mruby-gems/mruby-idnarray-image'
  # ...
end
```

## Usage:
```ruby
img = NArray::Image.new 512, 512
img[0, 0] = [255, 255, 255, 255]
img[0, 0] #=> [255, 255, 255, 255]


# Interfaces nicely with mruby-nanovg-idnarray-image
ctx #=> Nanovg::Context
ctx.create_image_rgba_narray(img.width, img.height, Nanovg::NO_FLAG, img.narray)
```

## Docs
```shell
# to generate docs locally
rake docs
```
