#include "ds/text_wrapper.hpp"

#include <cctype>
#include <ostream>
#include <stdexcept>

namespace ds {

namespace {
int compute_wrapped_lines(const char* text, int width) {
    if (text == nullptr || text[0] == '\0') return 0;
    int lines = 1;
    int current = 0;
    int word_len = 0;
    for (const char* p = text;; ++p) {
        char ch = *p;
        bool is_separator = (ch == '\0' || ch == '\n' || std::isspace(static_cast<unsigned char>(ch)));
        if (!is_separator) {
            ++word_len;
            continue;
        }
        if (word_len > 0) {
            int remaining = word_len;
            while (remaining > 0) {
                int chunk = remaining > width ? width : remaining;
                if (current == 0) {
                    current = chunk;
                } else if (current + 1 + chunk <= width) {
                    current += 1 + chunk;
                } else {
                    ++lines;
                    current = chunk;
                }
                remaining -= chunk;
                if (remaining > 0) {
                    ++lines;
                    current = 0;
                }
            }
            word_len = 0;
        }
        if (ch == '\n') {
            ++lines;
            current = 0;
        }
        if (ch == '\0') break;
    }
    return lines;
}
}

TextWrapper::TextWrapper(const MyString& text, int width) : text_(text), width_(width) {
    if (width <= 0) throw std::invalid_argument("wrap width must be positive");
}

int TextWrapper::count_lines() const {
    return compute_wrapped_lines(text_.c_str(), width_);
}

int TextWrapper::count_lines(const MyString& text, int width) {
    if (width <= 0) return 0;
    return compute_wrapped_lines(text.c_str(), width);
}

void TextWrapper::print_wrapped(std::ostream& os) const {
    const char* text = text_.c_str();
    int current = 0;
    int word_start = -1;
    int word_len = 0;

    auto flush_word = [&](int start, int len) {
        int remaining = len;
        int pos = start;
        while (remaining > 0) {
            int chunk = remaining > width_ ? width_ : remaining;
            if (current == 0) {
                for (int i = 0; i < chunk; ++i) os << text[pos + i];
                current = chunk;
            } else if (current + 1 + chunk <= width_) {
                os << ' ';
                for (int i = 0; i < chunk; ++i) os << text[pos + i];
                current += 1 + chunk;
            } else {
                os << '\n';
                for (int i = 0; i < chunk; ++i) os << text[pos + i];
                current = chunk;
            }
            pos += chunk;
            remaining -= chunk;
            if (remaining > 0) {
                os << '\n';
                current = 0;
            }
        }
    };

    for (int i = 0;; ++i) {
        char ch = text[i];
        bool is_separator = (ch == '\0' || ch == '\n' || std::isspace(static_cast<unsigned char>(ch)));
        if (!is_separator) {
            if (word_len == 0) word_start = i;
            ++word_len;
            continue;
        }
        if (word_len > 0) {
            flush_word(word_start, word_len);
            word_len = 0;
            word_start = -1;
        }
        if (ch == '\n') {
            os << '\n';
            current = 0;
        }
        if (ch == '\0') break;
    }
}

}  // namespace ds
