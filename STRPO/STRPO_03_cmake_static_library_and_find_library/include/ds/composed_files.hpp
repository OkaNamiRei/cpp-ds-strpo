#pragma once

#include "ds/ifile.hpp"

#include <cstddef>

namespace ds {

class Base32File2 : public IFile {
public:
    explicit Base32File2(IFile* inner, const char* alphabet = nullptr);
    ~Base32File2() override;

    Base32File2(const Base32File2&) = delete;
    Base32File2& operator=(const Base32File2&) = delete;

    bool can_read() const override;
    bool can_write() const override;
    std::size_t read(void* buf, std::size_t max_bytes) override;
    std::size_t write(const void* buf, std::size_t n_bytes) override;

private:
    IFile* inner_;
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

class RleFile2 : public IFile {
public:
    explicit RleFile2(IFile* inner);
    ~RleFile2() override;

    RleFile2(const RleFile2&) = delete;
    RleFile2& operator=(const RleFile2&) = delete;

    bool can_read() const override;
    bool can_write() const override;
    std::size_t read(void* buf, std::size_t max_bytes) override;
    std::size_t write(const void* buf, std::size_t n_bytes) override;

private:
    IFile* inner_;
    unsigned char* decoded_cache_;
    std::size_t decoded_size_;
    std::size_t decoded_offset_;
    std::size_t decoded_capacity_;

    void reset_cache();
    void ensure_cache_capacity(std::size_t capacity);
    bool read_exact(void* buf, std::size_t bytes);
};

}  // namespace ds
