#pragma once

#include "ds/point.hpp"

#include <iosfwd>

namespace ds {

class Circle {
public:
    Circle();
    Circle(const Point& center, double radius);
    Circle(double x, double y, double radius);

    const Point& center() const;
    double radius() const;
    double area() const;

    void set_center(const Point& center);
    void set_radius(double radius);

private:
    Point center_;
    double radius_;
};

bool operator==(const Circle& lhs, const Circle& rhs);
bool operator!=(const Circle& lhs, const Circle& rhs);
std::ostream& operator<<(std::ostream& os, const Circle& circle);
std::istream& operator>>(std::istream& is, Circle& circle);

}  // namespace ds
