#include "ds/base_file.hpp"
#include "ds/base32_file.hpp"
#include "ds/rle_file.hpp"

#include <cassert>
#include <cstdio>

int main() {
    const int value = 123456;
    {
        ds::BaseFile file("plain.bin", "wb");
        ds::write_int(file, value);
    }
    {
        ds::Base32File file("b32.bin", "wb");
        ds::write_int(file, value);
    }
    {
        ds::RleFile file("rle.bin", "wb");
        ds::write_int(file, value);
    }
    {
        ds::BaseFile file("plain.bin", "rb");
        assert(ds::read_int(file) == value);
    }
    {
        ds::Base32File file("b32.bin", "rb");
        assert(ds::read_int(file) == value);
    }
    {
        ds::RleFile file("rle.bin", "rb");
        assert(ds::read_int(file) == value);
    }
    std::remove("plain.bin"); std::remove("b32.bin"); std::remove("rle.bin");
    return 0;
}
