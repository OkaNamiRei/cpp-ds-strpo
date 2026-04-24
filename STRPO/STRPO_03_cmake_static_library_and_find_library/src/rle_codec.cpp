#include "ds/rle_codec.hpp"

namespace ds {

std::size_t RleCodec::encode(const unsigned char* src, std::size_t size, unsigned char* dst) {
    std::size_t out = 0;
    for (std::size_t i = 0; i < size;) {
        unsigned char value = src[i];
        unsigned char count = 1;
        while (i + count < size && src[i + count] == value && count < 255) ++count;
        dst[out++] = count;
        dst[out++] = value;
        i += count;
    }
    return out;
}

std::size_t RleCodec::decode(const unsigned char* src, std::size_t size, unsigned char* dst) {
    std::size_t out = 0;
    for (std::size_t i = 0; i + 1 < size; i += 2) {
        unsigned char count = src[i];
        unsigned char value = src[i + 1];
        for (unsigned char j = 0; j < count; ++j) dst[out++] = value;
    }
    return out;
}

}  // namespace ds
