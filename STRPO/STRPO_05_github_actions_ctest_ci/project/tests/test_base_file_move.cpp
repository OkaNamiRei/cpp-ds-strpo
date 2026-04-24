#include "ds/base_file.hpp"

#include <cassert>
#include <cstdio>
#include <utility>

int main() {
    using namespace ds;
    {
        BaseFile first("move_file.txt", "wb");
        BaseFile second = std::move(first);
        write_int(second, 42);
    }
    {
        BaseFile file("move_file.txt", "rb");
        assert(read_int(file) == 42);
    }
    std::remove("move_file.txt");
    return 0;
}
