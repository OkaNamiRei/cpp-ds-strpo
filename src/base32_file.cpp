#include "ds/base32_file.hpp"
#include "ds/base32_codec.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <utility>

namespace ds {

namespace {
constexpr const char* kDefaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
constexpr std::size_t encoded_capacity_for(std::size_t bytes) {
    return ((bytes * 8u) + 4u) / 5u + 8u;
}
}

Base32File::Base32File()
    : BaseFile(), alphabet_{}, decoded_cache_(nullptr), decoded_size_(0), decoded_offset_(0), decoded_capacity_(0) {
    init_alphabet(nullptr);
}

Base32File::Base32File(const char* path, const char* mode, const char* alphabet)
    : BaseFile(path, mode), alphabet_{}, decoded_cache_(nullptr), decoded_size_(0), decoded_offset_(0), decoded_capacity_(0) {
    init_alphabet(alphabet);
}

Base32File::Base32File(FILE* file_ptr, const char* alphabet)
    : BaseFile(file_ptr), alphabet_{}, decoded_cache_(nullptr), decoded_size_(0), decoded_offset_(0), decoded_capacity_(0) {
    init_alphabet(alphabet);
}

Base32File::~Base32File() { delete[] decoded_cache_; }

Base32File::Base32File(Base32File&& other) noexcept
    : BaseFile(std::move(other)), alphabet_{}, decoded_cache_(other.decoded_cache_), decoded_size_(other.decoded_size_),
      decoded_offset_(other.decoded_offset_), decoded_capacity_(other.decoded_capacity_) {
    std::memcpy(alphabet_, other.alphabet_, sizeof(alphabet_));
    other.decoded_cache_ = nullptr;
    other.decoded_size_ = 0;
    other.decoded_offset_ = 0;
    other.decoded_capacity_ = 0;
    other.init_alphabet(nullptr);
}

Base32File& Base32File::operator=(Base32File&& other) noexcept {
    if (this != &other) {
        BaseFile::operator=(std::move(other));
        delete[] decoded_cache_;
        std::memcpy(alphabet_, other.alphabet_, sizeof(alphabet_));
        decoded_cache_ = other.decoded_cache_;
        decoded_size_ = other.decoded_size_;
        decoded_offset_ = other.decoded_offset_;
        decoded_capacity_ = other.decoded_capacity_;
        other.decoded_cache_ = nullptr;
        other.decoded_size_ = 0;
        other.decoded_offset_ = 0;
        other.decoded_capacity_ = 0;
        other.init_alphabet(nullptr);
    }
    return *this;
}

void Base32File::init_alphabet(const char* alphabet) {
    const char* source = alphabet == nullptr ? kDefaultAlphabet : alphabet;
    std::memset(alphabet_, 0, sizeof(alphabet_));
    std::strncpy(alphabet_, source, 32);
    alphabet_[32] = 0;
}

void Base32File::reset_cache() {
    decoded_size_ = 0;
    decoded_offset_ = 0;
}

void Base32File::ensure_cache_capacity(std::size_t capacity) {
    if (capacity <= decoded_capacity_) return;
    delete[] decoded_cache_;
    decoded_cache_ = new unsigned char[capacity];
    decoded_capacity_ = capacity;
    reset_cache();
}

bool Base32File::read_exact(void* buf, std::size_t bytes) {
    unsigned char* out = static_cast<unsigned char*>(buf);
    std::size_t done = 0;
    while (done < bytes) {
        std::size_t current = read_raw(out + done, bytes - done);
        if (current == 0) return false;
        done += current;
    }
    return true;
}

std::size_t Base32File::write(const void* buf, std::size_t n_bytes) {
    const unsigned char* src = static_cast<const unsigned char*>(buf);
    const std::size_t encoded_capacity = encoded_capacity_for(n_bytes);
    char* encoded = new char[encoded_capacity];
    const std::size_t encoded_size = Base32Codec::encode(src, n_bytes, encoded, alphabet_);
    std::uint32_t original_size = static_cast<std::uint32_t>(n_bytes);
    std::uint32_t stored_size = static_cast<std::uint32_t>(encoded_size);
    bool ok = write_raw(&original_size, sizeof(original_size)) == sizeof(original_size) &&
              write_raw(&stored_size, sizeof(stored_size)) == sizeof(stored_size) &&
              write_raw(encoded, encoded_size) == encoded_size;
    delete[] encoded;
    return ok ? n_bytes : 0;
}

std::size_t Base32File::read(void* buf, std::size_t max_bytes) {
    unsigned char* out = static_cast<unsigned char*>(buf);
    std::size_t total = 0;
    while (total < max_bytes) {
        if (decoded_offset_ < decoded_size_) {
            std::size_t available = decoded_size_ - decoded_offset_;
            std::size_t chunk = std::min(available, max_bytes - total);
            std::memcpy(out + total, decoded_cache_ + decoded_offset_, chunk);
            decoded_offset_ += chunk;
            total += chunk;
            continue;
        }

        std::uint32_t original_size = 0;
        std::uint32_t encoded_size = 0;
        if (!read_exact(&original_size, sizeof(original_size))) break;
        if (!read_exact(&encoded_size, sizeof(encoded_size))) {
            throw std::runtime_error("corrupted Base32File frame");
        }
        char* encoded = new char[encoded_size == 0 ? 1 : encoded_size];
        if (!read_exact(encoded, encoded_size)) {
            delete[] encoded;
            throw std::runtime_error("corrupted Base32File payload");
        }
        ensure_cache_capacity(original_size == 0 ? 1 : original_size);
        decoded_size_ = Base32Codec::decode(encoded, encoded_size, decoded_cache_, alphabet_);
        decoded_offset_ = 0;
        delete[] encoded;
    }
    return total;
}

}  // namespace ds
