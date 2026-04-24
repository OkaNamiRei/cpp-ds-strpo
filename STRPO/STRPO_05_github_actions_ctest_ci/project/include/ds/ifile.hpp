#pragma once

#include <cstddef>

namespace ds {

class IFile {
public:
    virtual ~IFile() = default;
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual std::size_t read(void* buf, std::size_t max_bytes) = 0;
    virtual std::size_t write(const void* buf, std::size_t n_bytes) = 0;
};

}  // namespace ds
