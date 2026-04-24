#pragma once

#include <iosfwd>

namespace ds {

class Point {
public:
    Point();
    Point(double x, double y);

    double x() const;
    double y() const;

    void set_x(double x);
    void set_y(double y);
    void set(double x, double y);

private:
    double x_;
    double y_;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
std::ostream& operator<<(std::ostream& os, const Point& point);
std::istream& operator>>(std::istream& is, Point& point);

}  // namespace ds
