#include "ds/bool_array.hpp"

#include <cstring>
#include <stdexcept>

namespace ds {

BoolArray::BitReference::BitReference(unsigned char* byte, unsigned char mask) : byte_(byte), mask_(mask) {}
BoolArray::BitReference& BoolArray::BitReference::operator=(bool value) { if (value) *byte_ |= mask_; else *byte_ &= static_cast<unsigned char>(~mask_); return *this; }
BoolArray::BitReference& BoolArray::BitReference::operator=(const BitReference& other) { return (*this = static_cast<bool>(other)); }
BoolArray::BitReference::operator bool() const { return (*byte_ & mask_) != 0; }
bool BoolArray::BitReference::operator!() const { return !static_cast<bool>(*this); }

BoolArray::BoolArray() : data_(nullptr), size_(0), capacity_bytes_(0) {}
BoolArray::BoolArray(std::size_t size, bool value) : data_(nullptr), size_(size), capacity_bytes_(bytes_for_size(size)) {
    data_ = capacity_bytes_ == 0 ? nullptr : new unsigned char[capacity_bytes_];
    if (capacity_bytes_ > 0) std::memset(data_, value ? 0xFF : 0x00, capacity_bytes_);
    if (value && size_ % 8 != 0 && capacity_bytes_ > 0) data_[capacity_bytes_ - 1] &= static_cast<unsigned char>((1u << (size_ % 8)) - 1u);
}
BoolArray::BoolArray(const BoolArray& other) : data_(nullptr), size_(other.size_), capacity_bytes_(other.capacity_bytes_) {
    if (capacity_bytes_ > 0) { data_ = new unsigned char[capacity_bytes_]; std::memcpy(data_, other.data_, capacity_bytes_); }
}
BoolArray::BoolArray(BoolArray&& other) noexcept : data_(other.data_), size_(other.size_), capacity_bytes_(other.capacity_bytes_) {
    other.data_ = nullptr; other.size_ = 0; other.capacity_bytes_ = 0;
}
BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        unsigned char* new_data = other.capacity_bytes_ ? new unsigned char[other.capacity_bytes_] : nullptr;
        if (other.capacity_bytes_ > 0) std::memcpy(new_data, other.data_, other.capacity_bytes_);
        delete[] data_;
        data_ = new_data; size_ = other.size_; capacity_bytes_ = other.capacity_bytes_;
    }
    return *this;
}
BoolArray& BoolArray::operator=(BoolArray&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_; size_ = other.size_; capacity_bytes_ = other.capacity_bytes_;
        other.data_ = nullptr; other.size_ = 0; other.capacity_bytes_ = 0;
    }
    return *this;
}
BoolArray::~BoolArray() { delete[] data_; }

std::size_t BoolArray::bytes_for_size(std::size_t size) { return (size + 7) / 8; }
void BoolArray::ensure_index(std::size_t index) const { if (index >= size_) throw std::out_of_range("BoolArray index out of range"); }
bool BoolArray::get_bit(std::size_t index) const {
    ensure_index(index);
    std::size_t byte_index = index / 8;
    unsigned char mask = static_cast<unsigned char>(1u << (index % 8));
    return (data_[byte_index] & mask) != 0;
}
std::size_t BoolArray::size() const { return size_; }

void BoolArray::resize(std::size_t new_size, bool fill_value) {
    std::size_t new_bytes = bytes_for_size(new_size);
    unsigned char* new_data = new_bytes == 0 ? nullptr : new unsigned char[new_bytes];
    if (new_bytes > 0) std::memset(new_data, 0, new_bytes);
    std::size_t common = new_size < size_ ? new_size : size_;
    for (std::size_t i = 0; i < common; ++i) {
        if ((*this)[i]) {
            std::size_t byte_index = i / 8;
            unsigned char mask = static_cast<unsigned char>(1u << (i % 8));
            new_data[byte_index] |= mask;
        }
    }
    for (std::size_t i = common; i < new_size; ++i) {
        if (fill_value) {
            std::size_t byte_index = i / 8;
            unsigned char mask = static_cast<unsigned char>(1u << (i % 8));
            new_data[byte_index] |= mask;
        }
    }
    delete[] data_;
    data_ = new_data; size_ = new_size; capacity_bytes_ = new_bytes;
}

BoolArray::BitReference BoolArray::operator[](std::size_t index) {
    ensure_index(index);
    std::size_t byte_index = index / 8;
    unsigned char mask = static_cast<unsigned char>(1u << (index % 8));
    return BitReference(&data_[byte_index], mask);
}

bool BoolArray::operator[](std::size_t index) const { return get_bit(index); }

}  // namespace ds
