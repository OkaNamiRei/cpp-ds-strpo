#pragma once

#include "ds/base_file.hpp"

#include <cstddef>

namespace ds {

class Base32File : public BaseFile {
public:
    Base32File();
    Base32File(const char* path, const char* mode, const char* alphabet = nullptr);
    explicit Base32File(FILE* file_ptr, const char* alphabet = nullptr);
    ~Base32File() override;

    Base32File(const Base32File&) = delete;
    Base32File& operator=(const Base32File&) = delete;
    Base32File(Base32File&& other) noexcept;
    Base32File& operator=(Base32File&& other) noexcept;

    std::size_t read(void* buf, std::size_t max_bytes) override;
    std::size_t write(const void* buf, std::size_t n_bytes) override;

private:
    char alphabet_[33];
    unsigned char* decoded_cache_;
    std::size_t decoded_size_;
    std::size_t decoded_offset_;
    std::size_t decoded_capacity_;

    void init_alphabet(const char* alphabet);
    void reset_cache();
    void ensure_cache_capacity(std::size_t capacity);
    bool read_exact(void* buf, std::size_t bytes);
};

}  // namespace ds
