#pragma once

#include <cstddef>
#include <iosfwd>
#include <istream>
#include <iostream>

namespace ds {

class MyString {
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    MyString& operator=(const char* str);

    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print() const;
    void read_line(std::istream& in = std::cin);

    const char* c_str() const;
    std::size_t length() const;
    bool empty() const;

    char& operator[](int i);
    const char& operator[](int i) const;

    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char* str);

    MyString operator+(const MyString& other) const;
    MyString operator+(const char* str) const;

    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator>=(const MyString& other) const;

    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;
    bool operator<(const char* str) const;
    bool operator<=(const char* str) const;
    bool operator>(const char* str) const;
    bool operator>=(const char* str) const;

    static int compare_cstr(const char* lhs, const char* rhs);

private:
    char* data_;
    std::size_t size_;

    void assign_from_cstr(const char* str);
    void append_cstr(const char* str);
};

MyString operator+(const char* lhs, const MyString& rhs);
bool operator==(const char* lhs, const MyString& rhs);
bool operator!=(const char* lhs, const MyString& rhs);
bool operator<(const char* lhs, const MyString& rhs);
bool operator<=(const char* lhs, const MyString& rhs);
bool operator>(const char* lhs, const MyString& rhs);
bool operator>=(const char* lhs, const MyString& rhs);
std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);

}  // namespace ds
