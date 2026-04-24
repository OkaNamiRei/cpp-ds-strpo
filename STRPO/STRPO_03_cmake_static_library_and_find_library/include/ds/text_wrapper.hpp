#pragma once

#include "ds/my_string.hpp"

#include <iosfwd>

namespace ds {

class TextWrapper {
public:
    TextWrapper(const MyString& text, int width);

    int count_lines() const;
    void print_wrapped(std::ostream& os = std::cout) const;

    static int count_lines(const MyString& text, int width);

private:
    MyString text_;
    int width_;
};

}  // namespace ds
