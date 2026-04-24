#pragma once

#include "ds/ifile.hpp"

#include <cstddef>
#include <cstdio>

namespace ds {

class BaseFile : public IFile {
public:
    BaseFile();
    BaseFile(const char* path, const char* mode);
    explicit BaseFile(FILE* file_ptr);
    BaseFile(const BaseFile&) = delete;
    BaseFile& operator=(const BaseFile&) = delete;
    BaseFile(BaseFile&& other) noexcept;
    BaseFile& operator=(BaseFile&& other) noexcept;
    ~BaseFile() override;

    bool is_open() const;
    bool can_read() const override;
    bool can_write() const override;

    std::size_t write_raw(const void* buf, std::size_t n_bytes);
    std::size_t read_raw(void* buf, std::size_t max_bytes);
    long tell() const;
    bool seek(long offset);

    std::size_t read(void* buf, std::size_t max_bytes) override;
    std::size_t write(const void* buf, std::size_t n_bytes) override;

protected:
    FILE* native_handle() const;

private:
    FILE* file_;
    bool owns_;
    bool readable_;
    bool writable_;

    void close_if_needed();
    void init_mode_flags(const char* mode);
};

void write_int(IFile& file, int value);
int read_int(IFile& file);

}  // namespace ds
