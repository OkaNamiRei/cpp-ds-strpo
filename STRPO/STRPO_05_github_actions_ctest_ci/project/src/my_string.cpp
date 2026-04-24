#include "ds/my_string.hpp"

#include <cstring>
#include <stdexcept>

namespace ds {

namespace {
char* allocate_copy(const char* str, std::size_t& out_size) {
    if (str == nullptr) {
        out_size = 0;
        char* result = new char[1];
        result[0] = '\0';
        return result;
    }
    out_size = std::strlen(str);
    char* result = new char[out_size + 1];
    std::memcpy(result, str, out_size + 1);
    return result;
}
}  // namespace

MyString::MyString() : data_(new char[1]), size_(0) { data_[0] = '\0'; }
MyString::MyString(const char* str) : data_(nullptr), size_(0) { data_ = allocate_copy(str, size_); }
MyString::MyString(const MyString& other) : data_(nullptr), size_(0) { data_ = allocate_copy(other.data_, size_); }
MyString::MyString(MyString&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = new char[1];
    other.data_[0] = '\0';
    other.size_ = 0;
}
MyString::~MyString() { delete[] data_; }

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        std::size_t new_size = 0;
        char* new_data = allocate_copy(other.data_, new_size);
        delete[] data_;
        data_ = new_data;
        size_ = new_size;
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = new char[1];
        other.data_[0] = '\0';
        other.size_ = 0;
    }
    return *this;
}

MyString& MyString::operator=(const char* str) { assign_from_cstr(str); return *this; }

void MyString::assign_from_cstr(const char* str) {
    std::size_t new_size = 0;
    char* new_data = allocate_copy(str, new_size);
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

void MyString::append_cstr(const char* str) {
    if (str == nullptr || str[0] == '\0') return;
    std::size_t rhs_size = std::strlen(str);
    char* new_data = new char[size_ + rhs_size + 1];
    std::memcpy(new_data, data_, size_);
    std::memcpy(new_data + size_, str, rhs_size + 1);
    delete[] data_;
    data_ = new_data;
    size_ += rhs_size;
}

int MyString::compare_cstr(const char* lhs, const char* rhs) {
    return std::strcmp(lhs == nullptr ? "" : lhs, rhs == nullptr ? "" : rhs);
}

char MyString::get(int i) const {
    if (i < 0 || static_cast<std::size_t>(i) >= size_) throw std::out_of_range("MyString index out of range");
    return data_[i];
}

void MyString::set(int i, char c) {
    if (i < 0 || static_cast<std::size_t>(i) >= size_) throw std::out_of_range("MyString index out of range");
    data_[i] = c;
}

void MyString::set_new_string(const char* str) { assign_from_cstr(str); }
void MyString::print() const { std::cout << data_; }

void MyString::read_line(std::istream& in) {
    constexpr std::size_t chunk = 64;
    char* buffer = new char[chunk];
    std::size_t capacity = chunk;
    std::size_t length = 0;
    while (true) {
        int value = in.get();
        if (value == EOF || value == '\n') break;
        if (length + 1 >= capacity) {
            std::size_t new_capacity = capacity * 2;
            char* new_buffer = new char[new_capacity];
            std::memcpy(new_buffer, buffer, length);
            delete[] buffer;
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = static_cast<char>(value);
    }
    buffer[length] = '\0';
    delete[] data_;
    data_ = buffer;
    size_ = length;
}

const char* MyString::c_str() const { return data_; }
std::size_t MyString::length() const { return size_; }
bool MyString::empty() const { return size_ == 0; }

char& MyString::operator[](int i) {
    if (i < 0 || static_cast<std::size_t>(i) >= size_) throw std::out_of_range("MyString index out of range");
    return data_[i];
}

const char& MyString::operator[](int i) const {
    if (i < 0 || static_cast<std::size_t>(i) >= size_) throw std::out_of_range("MyString index out of range");
    return data_[i];
}

MyString& MyString::operator+=(const MyString& other) { append_cstr(other.data_); return *this; }
MyString& MyString::operator+=(const char* str) { append_cstr(str); return *this; }
MyString MyString::operator+(const MyString& other) const { MyString result(*this); result += other; return result; }
MyString MyString::operator+(const char* str) const { MyString result(*this); result += str; return result; }

bool MyString::operator==(const MyString& other) const { return compare_cstr(data_, other.data_) == 0; }
bool MyString::operator!=(const MyString& other) const { return !(*this == other); }
bool MyString::operator<(const MyString& other) const { return compare_cstr(data_, other.data_) < 0; }
bool MyString::operator<=(const MyString& other) const { return compare_cstr(data_, other.data_) <= 0; }
bool MyString::operator>(const MyString& other) const { return compare_cstr(data_, other.data_) > 0; }
bool MyString::operator>=(const MyString& other) const { return compare_cstr(data_, other.data_) >= 0; }

bool MyString::operator==(const char* str) const { return compare_cstr(data_, str) == 0; }
bool MyString::operator!=(const char* str) const { return !(*this == str); }
bool MyString::operator<(const char* str) const { return compare_cstr(data_, str) < 0; }
bool MyString::operator<=(const char* str) const { return compare_cstr(data_, str) <= 0; }
bool MyString::operator>(const char* str) const { return compare_cstr(data_, str) > 0; }
bool MyString::operator>=(const char* str) const { return compare_cstr(data_, str) >= 0; }

MyString operator+(const char* lhs, const MyString& rhs) { MyString result(lhs); result += rhs; return result; }
bool operator==(const char* lhs, const MyString& rhs) { return rhs == lhs; }
bool operator!=(const char* lhs, const MyString& rhs) { return !(lhs == rhs); }
bool operator<(const char* lhs, const MyString& rhs) { return MyString::compare_cstr(lhs, rhs.c_str()) < 0; }
bool operator<=(const char* lhs, const MyString& rhs) { return MyString::compare_cstr(lhs, rhs.c_str()) <= 0; }
bool operator>(const char* lhs, const MyString& rhs) { return MyString::compare_cstr(lhs, rhs.c_str()) > 0; }
bool operator>=(const char* lhs, const MyString& rhs) { return MyString::compare_cstr(lhs, rhs.c_str()) >= 0; }
std::ostream& operator<<(std::ostream& os, const MyString& str) { os << str.c_str(); return os; }
std::istream& operator>>(std::istream& is, MyString& str) { str.read_line(is); return is; }

}  // namespace ds
