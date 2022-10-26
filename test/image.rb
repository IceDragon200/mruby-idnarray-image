assert 'NArray::Image#initialize' do
  img = NArray::Image.new 512, 512

  assert_equal img.w, 512
  assert_equal img.h, 512
end

assert 'NArray::Image#(get|set)_pixel' do
  img = NArray::Image.new 512, 512

  assert_equal img.w, 512
  assert_equal img.h, 512

  [[0, 0], [256, 256], [511, 511]].each do |(x, y)|
    img.set_pixel(x, y, 0, 1, 4, 200)
    pixel = img.get_pixel(x, y)

    assert_equal 0, pixel[0]
    assert_equal 1, pixel[1]
    assert_equal 4, pixel[2]
    assert_equal 200, pixel[3]
  end

  img.set_pixel(512, 512, 0, 1, 4, 200)
  pixel = img.get_pixel(512, 512)

  assert_equal 0, pixel[0]
  assert_equal 0, pixel[1]
  assert_equal 0, pixel[2]
  assert_equal 0, pixel[3]
end
