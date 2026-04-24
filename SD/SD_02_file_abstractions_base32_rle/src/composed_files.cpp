#include "ds/composed_files.hpp"
#include "ds/base32_codec.hpp"
#include "ds/rle_codec.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace ds {

namespace {
constexpr const char* kDefaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
constexpr std::size_t base32_capacity_for(std::size_t bytes) {
    return ((bytes * 8u) + 4u) / 5u + 8u;
}
constexpr std::size_t rle_capacity_for(std::size_t bytes) {
    return bytes == 0 ? 1 : bytes * 2;
}
}

Base32File2::Base32File2(IFile* inner, const char* alphabet)
    : inner_(inner), alphabet_{}, decoded_cache_(nullptr), decoded_size_(0), decoded_offset_(0), decoded_capacity_(0) {
    init_alphabet(alphabet);
}

Base32File2::~Base32File2() {
    delete[] decoded_cache_;
    delete inner_;
}

void Base32File2::init_alphabet(const char* alphabet) {
    const char* source = alphabet == nullptr ? kDefaultAlphabet : alphabet;
    std::memset(alphabet_, 0, sizeof(alphabet_));
    std::strncpy(alphabet_, source, 32);
    alphabet_[32] = 0;
}

void Base32File2::reset_cache() {
    decoded_size_ = 0;
    decoded_offset_ = 0;
}

void Base32File2::ensure_cache_capacity(std::size_t capacity) {
    if (capacity <= decoded_capacity_) return;
    delete[] decoded_cache_;
    decoded_cache_ = new unsigned char[capacity];
    decoded_capacity_ = capacity;
    reset_cache();
}

bool Base32File2::read_exact(void* buf, std::size_t bytes) {
    unsigned char* out = static_cast<unsigned char*>(buf);
    std::size_t done = 0;
    while (done < bytes) {
        std::size_t current = inner_->read(out + done, bytes - done);
        if (current == 0) return false;
        done += current;
    }
    return true;
}

bool Base32File2::can_read() const { return inner_ != nullptr && inner_->can_read(); }
bool Base32File2::can_write() const { return inner_ != nullptr && inner_->can_write(); }

std::size_t Base32File2::write(const void* buf, std::size_t n_bytes) {
    const unsigned char* src = static_cast<const unsigned char*>(buf);
    char* encoded = new char[base32_capacity_for(n_bytes)];
    const std::size_t encoded_size = Base32Codec::encode(src, n_bytes, encoded, alphabet_);
    std::uint32_t original_size = static_cast<std::uint32_t>(n_bytes);
    std::uint32_t stored_size = static_cast<std::uint32_t>(encoded_size);
    bool ok = inner_->write(&original_size, sizeof(original_size)) == sizeof(original_size) &&
              inner_->write(&stored_size, sizeof(stored_size)) == sizeof(stored_size) &&
              inner_->write(encoded, encoded_size) == encoded_size;
    delete[] encoded;
    return ok ? n_bytes : 0;
}

std::size_t Base32File2::read(void* buf, std::size_t max_bytes) {
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
        if (!read_exact(&encoded_size, sizeof(encoded_size))) throw std::runtime_error("corrupted Base32File2 frame");
        char* encoded = new char[encoded_size == 0 ? 1 : encoded_size];
        if (!read_exact(encoded, encoded_size)) {
            delete[] encoded;
            throw std::runtime_error("corrupted Base32File2 payload");
        }
        ensure_cache_capacity(original_size == 0 ? 1 : original_size);
        decoded_size_ = Base32Codec::decode(encoded, encoded_size, decoded_cache_, alphabet_);
        decoded_offset_ = 0;
        delete[] encoded;
    }
    return total;
}

RleFile2::RleFile2(IFile* inner)
    : inner_(inner), decoded_cache_(nullptr), decoded_size_(0), decoded_offset_(0), decoded_capacity_(0) {}

RleFile2::~RleFile2() {
    delete[] decoded_cache_;
    delete inner_;
}

void RleFile2::reset_cache() {
    decoded_size_ = 0;
    decoded_offset_ = 0;
}

void RleFile2::ensure_cache_capacity(std::size_t capacity) {
    if (capacity <= decoded_capacity_) return;
    delete[] decoded_cache_;
    decoded_cache_ = new unsigned char[capacity];
    decoded_capacity_ = capacity;
    reset_cache();
}

bool RleFile2::read_exact(void* buf, std::size_t bytes) {
    unsigned char* out = static_cast<unsigned char*>(buf);
    std::size_t done = 0;
    while (done < bytes) {
        std::size_t current = inner_->read(out + done, bytes - done);
        if (current == 0) return false;
        done += current;
    }
    return true;
}

bool RleFile2::can_read() const { return inner_ != nullptr && inner_->can_read(); }
bool RleFile2::can_write() const { return inner_ != nullptr && inner_->can_write(); }

std::size_t RleFile2::write(const void* buf, std::size_t n_bytes) {
    const unsigned char* src = static_cast<const unsigned char*>(buf);
    unsigned char* encoded = new unsigned char[rle_capacity_for(n_bytes)];
    const std::size_t encoded_size = RleCodec::encode(src, n_bytes, encoded);
    std::uint32_t original_size = static_cast<std::uint32_t>(n_bytes);
    std::uint32_t stored_size = static_cast<std::uint32_t>(encoded_size);
    bool ok = inner_->write(&original_size, sizeof(original_size)) == sizeof(original_size) &&
              inner_->write(&stored_size, sizeof(stored_size)) == sizeof(stored_size) &&
              inner_->write(encoded, encoded_size) == encoded_size;
    delete[] encoded;
    return ok ? n_bytes : 0;
}

std::size_t RleFile2::read(void* buf, std::size_t max_bytes) {
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
        if (!read_exact(&encoded_size, sizeof(encoded_size))) throw std::runtime_error("corrupted RleFile2 frame");
        unsigned char* encoded = new unsigned char[encoded_size == 0 ? 1 : encoded_size];
        if (!read_exact(encoded, encoded_size)) {
            delete[] encoded;
            throw std::runtime_error("corrupted RleFile2 payload");
        }
        ensure_cache_capacity(original_size == 0 ? 1 : original_size);
        decoded_size_ = RleCodec::decode(encoded, encoded_size, decoded_cache_);
        decoded_offset_ = 0;
        delete[] encoded;
    }
    return total;
}

}  // namespace ds
