#include "ds/point.hpp"

#include <istream>
#include <ostream>

namespace ds {

Point::Point() : x_(0.0), y_(0.0) {}
Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::x() const { return x_; }
double Point::y() const { return y_; }

void Point::set_x(double x) { x_ = x; }
void Point::set_y(double y) { y_ = y; }
void Point::set(double x, double y) {
    x_ = x;
    y_ = y;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << '(' << point.x() << ", " << point.y() << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
    double x = 0.0;
    double y = 0.0;
    is >> x >> y;
    if (is) {
        point.set(x, y);
    }
    return is;
}

}  // namespace ds
