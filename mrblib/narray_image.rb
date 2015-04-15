class NArray::Image
  alias :set_pixel_rgba :set_pixel

  # @param [Integer] x
  # @param [Integer] y
  # @param [Integer] r
  # @param [Integer] g
  # @param [Integer] b
  # @param [Integer] a
  # @return [void]
  def set_pixel_rgb(x, y, r, g, b, a = 255)
    set_pixel_rgba(x, y, r, g, b, a)
  end

  # @param [Array<Integer>]
  # @return [void]
  def set_pixel_ary(x, y, ary)
    set_pixel_rgb(x, y, *ary)
  end

  # @param [Integer] x
  # @param [Integer] y
  # @overload set_pixel(x, y, r, g, b, a = 255)
  #   (see #set_pixel_rgb)
  # @overload set_pixel(x, y, ary)
  #   (see #set_pixel_ary)
  # @return [void]
  def set_pixel(x, y, *a)
    case a.size
    when 1
      set_pixel_ary(x, y, a.first)
    when 3, 4
      set_pixel_rgb(x, y, *a)
    else
      raise ArgumentError, "wrong argument count #{a.size + 2} (expected 3, 5, or 6)"
    end
  end
end
