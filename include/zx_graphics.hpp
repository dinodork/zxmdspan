#include <iostream>
#include <mdspan>

namespace zxspectrum {

using word_t = std::uint16_t;

/*
  How to translate the screen memory address:

  Byte         15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0
               --+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
  Coordinate    0| 0| 0|Y7|Y6|Y2|Y1|Y0|Y5|Y4|Y3|X4|X3|X2|X1|X0
*/
word_t byteAddress(std::uint8_t x_byte, std::uint8_t y_pixel) {
  word_t byte_offset = x_byte;
  byte_offset |= (y_pixel & 0x07) << 8;
  byte_offset |= (y_pixel & 0X38) << 2;
  byte_offset |= (y_pixel & 0xC0) << 5;
  return byte_offset;
}

// The ZX Spectrum image file is a memory area of 192 rows of 32 bytes each,
// addressable using a 16 bit machine word.
using ImageFile = Kokkos::extents<word_t, 32, 192>;

struct ByteLayout {
  template <class Extents> class mapping {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = ByteLayout;

    // The framework forces the mapping to be constructible from the extents
    // type, but we really don't have a need for that.
    mapping(ImageFile) {}

    constexpr index_type operator()(index_type x_byte,
                                    index_type y_pixel) const noexcept {
      return byteAddress(x_byte, y_pixel);
    }
  };
};

struct BitLayout {
  template <class Extents> class mapping {
  public:
    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = ByteLayout;

    // The framework forces the mapping to be constructible from the extents
    // type, but we really don't have a need for that.
    mapping(ImageFile) {}

    constexpr index_type operator()(index_type x_pixel,
                                    index_type y_pixel) const noexcept {
      return byteAddress(x_pixel / 8, y_pixel) * 8 + x_pixel % 8;
    }
  };
};

struct BitAccessorPolicy {
  struct BitReference;

  using element_type = bool;
  using data_handle_type = std::uint8_t *;
  using reference = BitReference;

  struct BitReference {
    data_handle_type p;
    word_t i;
    BitReference operator=(element_type v) {
      std::uint8_t mask = 0x80 >> i % 8;
      if (v) {
        (*p) |= mask; // set bit
      } else {
        (*p) &= ~mask; // clear bit
      }
      return *this;
    }
  };

  constexpr reference access(data_handle_type p, word_t i) const noexcept {
    return {p + i / 8, i};
  }
};

using ByteSpan = Kokkos::mdspan<std::uint8_t, ImageFile, ByteLayout>;
using BitSpan = Kokkos::mdspan<bool, ImageFile, BitLayout, BitAccessorPolicy>;

} // namespace zxspectrum
