#include "ds/base32_file.hpp"
#include "ds/base_file.hpp"
#include "ds/composed_files.hpp"
#include "ds/rle_file.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace {
void fill_pattern(unsigned char* data, std::size_t size) {
    unsigned int x = 0xC0FFEEu;
    for (std::size_t i = 0; i < size; ++i) {
        x = x * 1664525u + 1013904223u;
        data[i] = static_cast<unsigned char>((x >> 16) & 0xFFu);
        if (i % 31 == 0) data[i] = 0;
        if (i % 31 == 1) data[i] = 0;
        if (i % 31 == 2) data[i] = 0;
    }
}

template <typename FileT>
void roundtrip_named(const char* path) {
    constexpr std::size_t total_size = 50000;
    constexpr std::size_t chunk = 256;
    unsigned char original[total_size];
    unsigned char decoded[total_size];
    fill_pattern(original, total_size);

    {
        FileT file(path, "wb");
        for (std::size_t offset = 0; offset < total_size; offset += chunk) {
            std::size_t current = (offset + chunk <= total_size) ? chunk : (total_size - offset);
            assert(file.write(original + offset, current) == current);
        }
    }

    std::size_t decoded_size = 0;
    {
        FileT file(path, "rb");
        while (decoded_size < total_size) {
            std::size_t got = file.read(decoded + decoded_size, chunk);
            if (got == 0) break;
            decoded_size += got;
        }
    }

    assert(decoded_size == total_size);
    assert(std::memcmp(original, decoded, total_size) == 0);
    std::remove(path);
}
}

int main() {
    roundtrip_named<ds::BaseFile>("large_plain.bin");
    roundtrip_named<ds::Base32File>("large_b32.bin");
    roundtrip_named<ds::RleFile>("large_rle.bin");

    constexpr std::size_t total_size = 50000;
    constexpr std::size_t chunk = 256;
    unsigned char original[total_size];
    unsigned char decoded[total_size];
    fill_pattern(original, total_size);
    {
        ds::RleFile2 file(new ds::Base32File2(new ds::BaseFile("large_combo.bin", "wb")));
        for (std::size_t offset = 0; offset < total_size; offset += chunk) {
            std::size_t current = (offset + chunk <= total_size) ? chunk : (total_size - offset);
            assert(file.write(original + offset, current) == current);
        }
    }
    std::size_t decoded_size = 0;
    {
        ds::RleFile2 file(new ds::Base32File2(new ds::BaseFile("large_combo.bin", "rb")));
        while (decoded_size < total_size) {
            std::size_t got = file.read(decoded + decoded_size, chunk);
            if (got == 0) break;
            decoded_size += got;
        }
    }
    assert(decoded_size == total_size);
    assert(std::memcmp(original, decoded, total_size) == 0);
    std::remove("large_combo.bin");
    return 0;
}
