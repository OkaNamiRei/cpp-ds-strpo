#pragma once

#include <cstddef>

namespace ds {

class Base32Codec {
public:
    static std::size_t encode(const unsigned char* src, std::size_t size, char* dst,
                              const char* alphabet = nullptr);
    static std::size_t decode(const char* src, std::size_t size, unsigned char* dst,
                              const char* alphabet = nullptr);
};

}  // namespace ds
