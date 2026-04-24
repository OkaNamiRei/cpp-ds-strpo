#pragma once

#include <cstddef>

namespace ds {

class RleCodec {
public:
    static std::size_t encode(const unsigned char* src, std::size_t size, unsigned char* dst);
    static std::size_t decode(const unsigned char* src, std::size_t size, unsigned char* dst);
};

}  // namespace ds
