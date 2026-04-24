#include "ds/rect.hpp"

#include <algorithm>
#include <iostream>

namespace ds {

Rect::Rect() : left_(0), bottom_(0), width_(0), height_(0) {
    trace("default ctor", this);
}

Rect::Rect(int left, int right, int top, int bottom) : left_(0), bottom_(0), width_(0), height_(0) {
    normalize_from_sides(left, right, top, bottom);
    trace("param ctor", this);
}

Rect::Rect(const Rect& other)
    : left_(other.left_), bottom_(other.bottom_), width_(other.width_), height_(other.height_) {
    trace("copy ctor", this);
}

Rect::Rect(Rect&& other) noexcept
    : left_(other.left_), bottom_(other.bottom_), width_(other.width_), height_(other.height_) {
    other.left_ = 0;
    other.bottom_ = 0;
    other.width_ = 0;
    other.height_ = 0;
    trace("move ctor", this);
}

Rect::~Rect() {
    trace("dtor", this);
}

Rect& Rect::operator=(const Rect& other) {
    if (this != &other) {
        left_ = other.left_;
        bottom_ = other.bottom_;
        width_ = other.width_;
        height_ = other.height_;
    }
    return *this;
}

Rect& Rect::operator=(Rect&& other) noexcept {
    if (this != &other) {
        left_ = other.left_;
        bottom_ = other.bottom_;
        width_ = other.width_;
        height_ = other.height_;
        other.left_ = 0;
        other.bottom_ = 0;
        other.width_ = 0;
        other.height_ = 0;
    }
    return *this;
}

void Rect::normalize_from_sides(int left, int right, int top, int bottom) {
    left_ = std::min(left, right);
    bottom_ = std::min(bottom, top);
    width_ = std::max(left, right) - left_;
    height_ = std::max(bottom, top) - bottom_;
}

void Rect::trace(const char* what, const Rect* self) {
#ifdef DS_TRACE_LIFETIME
    std::cout << "[Rect] " << what << " this=" << self << '\n';
#else
    (void)what;
    (void)self;
#endif
}

int Rect::get_left() const { return left_; }
int Rect::get_right() const { return left_ + width_; }
int Rect::get_top() const { return bottom_ + height_; }
int Rect::get_bottom() const { return bottom_; }

void Rect::set_all(int left, int right, int top, int bottom) {
    normalize_from_sides(left, right, top, bottom);
}

void Rect::inflate(int amount) {
    inflate(amount, amount, amount, amount);
}

void Rect::inflate(int dw, int dh) {
    inflate(dw, dw, dh, dh);
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    int new_left = left_ - d_left;
    int new_right = get_right() + d_right;
    int new_top = get_top() + d_top;
    int new_bottom = bottom_ - d_bottom;
    normalize_from_sides(new_left, new_right, new_top, new_bottom);
}

void Rect::move(int dx, int dy) {
    left_ += dx;
    bottom_ += dy;
}

int Rect::get_width() const { return width_; }
int Rect::get_height() const { return height_; }
int Rect::get_square() const { return width_ * height_; }

void Rect::set_width(int width) {
    width_ = width < 0 ? 0 : width;
}

void Rect::set_height(int height) {
    height_ = height < 0 ? 0 : height;
}

Rect bounding_rect(Rect r1, Rect r2) {
    return Rect(
        std::min(r1.get_left(), r2.get_left()),
        std::max(r1.get_right(), r2.get_right()),
        std::max(r1.get_top(), r2.get_top()),
        std::min(r1.get_bottom(), r2.get_bottom())
    );
}

void print_rect(const Rect& r) {
    std::cout << r;
}

std::ostream& operator<<(std::ostream& os, const Rect& r) {
    os << "Rect{" << r.get_left() << ", " << r.get_right() << ", " << r.get_top() << ", " << r.get_bottom() << '}';
    return os;
}

}  // namespace ds
