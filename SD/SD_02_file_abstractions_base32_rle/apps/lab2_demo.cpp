#include "ds/base32_file.hpp"
#include "ds/base_file.hpp"
#include "ds/composed_files.hpp"
#include "ds/my_string.hpp"
#include "ds/rle_file.hpp"

#include <cstdio>
#include <iostream>

int main() {
    using namespace ds;
    MyString ar[5] = {MyString("one"), MyString("two"), MyString("three")};
    std::cout << "=== array of MyString ===\n";
    for (const MyString& s : ar) std::cout << '[' << s << "]\n";

    std::cout << "\n=== write_int through different file abstractions ===\n";
    {
        BaseFile file("lab2_plain.txt", "wb");
        write_int(file, 123456);
    }
    {
        Base32File file("lab2_b32.bin", "wb");
        write_int(file, 123456);
    }
    {
        RleFile file("lab2_rle.bin", "wb");
        write_int(file, 123456);
    }
    {
        RleFile2 file(new Base32File2(new BaseFile("lab2_combo.bin", "wb")));
        write_int(file, 123456);
    }

    {
        BaseFile file("lab2_plain.txt", "rb");
        std::cout << "plain -> " << read_int(file) << "\n";
    }
    {
        Base32File file("lab2_b32.bin", "rb");
        std::cout << "base32 -> " << read_int(file) << "\n";
    }
    {
        RleFile file("lab2_rle.bin", "rb");
        std::cout << "rle -> " << read_int(file) << "\n";
    }
    {
        RleFile2 file(new Base32File2(new BaseFile("lab2_combo.bin", "rb")));
        std::cout << "rle(base32(file)) -> " << read_int(file) << "\n";
    }

    std::remove("lab2_plain.txt");
    std::remove("lab2_b32.bin");
    std::remove("lab2_rle.bin");
    std::remove("lab2_combo.bin");
    return 0;
}
