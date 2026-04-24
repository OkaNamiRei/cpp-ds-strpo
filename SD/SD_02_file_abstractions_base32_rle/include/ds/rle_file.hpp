#pragma once

#include "ds/base_file.hpp"

#include <cstddef>

namespace ds {

class RleFile : public BaseFile {
public:
    RleFile();
    RleFile(const char* path, const char* mode);
    explicit RleFile(FILE* file_ptr);
    ~RleFile() override;

    RleFile(const RleFile&) = delete;
    RleFile& operator=(const RleFile&) = delete;
    RleFile(RleFile&& other) noexcept;
    RleFile& operator=(RleFile&& other) noexcept;

    std::size_t read(void* buf, std::size_t max_bytes) override;
    std::size_t write(const void* buf, std::size_t n_bytes) override;

private:
    unsigned char* decoded_cache_;
    std::size_t decoded_size_;
    std::size_t decoded_offset_;
    std::size_t decoded_capacity_;

    void reset_cache();
    void ensure_cache_capacity(std::size_t capacity);
    bool read_exact(void* buf, std::size_t bytes);
};

}  // namespace ds
