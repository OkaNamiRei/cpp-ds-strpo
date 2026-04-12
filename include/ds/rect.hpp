#pragma once

#include <iosfwd>

namespace ds {

class Rect {
public:
    Rect();
    Rect(int left, int right, int top, int bottom);
    Rect(const Rect& other);
    Rect(Rect&& other) noexcept;
    ~Rect();

    Rect& operator=(const Rect& other);
    Rect& operator=(Rect&& other) noexcept;

    int get_left() const;
    int get_right() const;
    int get_top() const;
    int get_bottom() const;

    void set_all(int left, int right, int top, int bottom);

    void inflate(int amount);
    void inflate(int dw, int dh);
    void inflate(int d_left, int d_right, int d_top, int d_bottom);

    void move(int dx = 0, int dy = 0);

    int get_width() const;
    int get_height() const;
    int get_square() const;

    void set_width(int width);
    void set_height(int height);

private:
    int left_;
    int bottom_;
    int width_;
    int height_;

    void normalize_from_sides(int left, int right, int top, int bottom);
    static void trace(const char* what, const Rect* self);
};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(const Rect& r);
std::ostream& operator<<(std::ostream& os, const Rect& r);

}  // namespace ds
