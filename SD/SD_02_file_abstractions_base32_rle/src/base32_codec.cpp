#include "ds/base32_codec.hpp"

namespace ds {

namespace {
const char* default_alphabet() {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
}
}

std::size_t Base32Codec::encode(const unsigned char* src, std::size_t size, char* dst, const char* alphabet) {
    if (alphabet == nullptr) alphabet = default_alphabet();
    std::size_t out = 0;
    unsigned int buffer = 0;
    int bits_left = 0;
    for (std::size_t i = 0; i < size; ++i) {
        buffer = (buffer << 8) | src[i];
        bits_left += 8;
        while (bits_left >= 5) {
            dst[out++] = alphabet[(buffer >> (bits_left - 5)) & 31u];
            bits_left -= 5;
        }
    }
    if (bits_left > 0) dst[out++] = alphabet[(buffer << (5 - bits_left)) & 31u];
    return out;
}

std::size_t Base32Codec::decode(const char* src, std::size_t size, unsigned char* dst, const char* alphabet) {
    if (alphabet == nullptr) alphabet = default_alphabet();
    auto value_of = [alphabet](char c) -> int {
        for (int i = 0; i < 32; ++i) {
            if (alphabet[i] == c) return i;
        }
        return -1;
    };
    std::size_t out = 0;
    unsigned int buffer = 0;
    int bits_left = 0;
    for (std::size_t i = 0; i < size; ++i) {
        int value = value_of(src[i]);
        if (value < 0) continue;
        buffer = (buffer << 5) | static_cast<unsigned int>(value);
        bits_left += 5;
        if (bits_left >= 8) {
            dst[out++] = static_cast<unsigned char>((buffer >> (bits_left - 8)) & 0xFFu);
            bits_left -= 8;
        }
    }
    return out;
}

}  // namespace ds
