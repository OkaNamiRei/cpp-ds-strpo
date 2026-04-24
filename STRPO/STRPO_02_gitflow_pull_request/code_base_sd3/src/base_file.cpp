#include "ds/base_file.hpp"

#include <cstring>
#include <stdexcept>
#include <string>

namespace ds {

BaseFile::BaseFile() : file_(nullptr), owns_(false), readable_(false), writable_(false) {}
BaseFile::BaseFile(const char* path, const char* mode)
    : file_(std::fopen(path, mode)), owns_(true), readable_(false), writable_(false) { init_mode_flags(mode); }
BaseFile::BaseFile(FILE* file_ptr) : file_(file_ptr), owns_(true), readable_(true), writable_(true) {}
BaseFile::BaseFile(BaseFile&& other) noexcept
    : file_(other.file_), owns_(other.owns_), readable_(other.readable_), writable_(other.writable_) {
    other.file_ = nullptr; other.owns_ = false; other.readable_ = false; other.writable_ = false;
}
BaseFile& BaseFile::operator=(BaseFile&& other) noexcept {
    if (this != &other) {
        close_if_needed();
        file_ = other.file_; owns_ = other.owns_; readable_ = other.readable_; writable_ = other.writable_;
        other.file_ = nullptr; other.owns_ = false; other.readable_ = false; other.writable_ = false;
    }
    return *this;
}
BaseFile::~BaseFile() { close_if_needed(); }

void BaseFile::init_mode_flags(const char* mode) {
    readable_ = mode != nullptr && (std::strchr(mode, 'r') != nullptr || std::strchr(mode, '+') != nullptr);
    writable_ = mode != nullptr && (std::strchr(mode, 'w') != nullptr || std::strchr(mode, 'a') != nullptr || std::strchr(mode, '+') != nullptr);
}

void BaseFile::close_if_needed() { if (owns_ && file_ != nullptr) std::fclose(file_); file_ = nullptr; }
bool BaseFile::is_open() const { return file_ != nullptr; }
bool BaseFile::can_read() const { return file_ != nullptr && readable_; }
bool BaseFile::can_write() const { return file_ != nullptr && writable_; }
std::size_t BaseFile::write_raw(const void* buf, std::size_t n_bytes) { return can_write() ? std::fwrite(buf, 1, n_bytes, file_) : 0; }
std::size_t BaseFile::read_raw(void* buf, std::size_t max_bytes) { return can_read() ? std::fread(buf, 1, max_bytes, file_) : 0; }
long BaseFile::tell() const { return file_ == nullptr ? -1 : std::ftell(file_); }
bool BaseFile::seek(long offset) { return file_ != nullptr && std::fseek(file_, offset, SEEK_SET) == 0; }
std::size_t BaseFile::read(void* buf, std::size_t max_bytes) { return read_raw(buf, max_bytes); }
std::size_t BaseFile::write(const void* buf, std::size_t n_bytes) { return write_raw(buf, n_bytes); }
FILE* BaseFile::native_handle() const { return file_; }

void write_int(IFile& file, int value) {
    char buffer[64];
    int length = std::snprintf(buffer, sizeof(buffer), "%d\n", value);
    if (length <= 0) throw std::runtime_error("failed to format integer");
    if (file.write(buffer, static_cast<std::size_t>(length)) != static_cast<std::size_t>(length)) {
        throw std::runtime_error("failed to write integer");
    }
}

int read_int(IFile& file) {
    char buffer[64];
    int length = 0;
    while (length + 1 < static_cast<int>(sizeof(buffer))) {
        char ch = '\0';
        std::size_t got = file.read(&ch, 1);
        if (got == 0) break;
        if (ch == '\n') break;
        buffer[length++] = ch;
    }
    buffer[length] = '\0';
    if (length == 0) throw std::runtime_error("failed to read integer");
    return std::stoi(buffer);
}

}  // namespace ds
