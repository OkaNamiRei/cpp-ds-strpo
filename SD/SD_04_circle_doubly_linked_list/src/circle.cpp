#include "ds/circle.hpp"

#include <cmath>
#include <istream>
#include <ostream>

namespace ds {

namespace {
constexpr double kPi = 3.14159265358979323846;
}

Circle::Circle() : center_(), radius_(0.0) {}
Circle::Circle(const Point& center, double radius) : center_(center), radius_(radius < 0.0 ? 0.0 : radius) {}
Circle::Circle(double x, double y, double radius) : center_(x, y), radius_(radius < 0.0 ? 0.0 : radius) {}

const Point& Circle::center() const { return center_; }
double Circle::radius() const { return radius_; }
double Circle::area() const { return kPi * radius_ * radius_; }

void Circle::set_center(const Point& center) { center_ = center; }
void Circle::set_radius(double radius) { radius_ = radius < 0.0 ? 0.0 : radius; }

bool operator==(const Circle& lhs, const Circle& rhs) {
    return lhs.center() == rhs.center() && lhs.radius() == rhs.radius();
}

bool operator!=(const Circle& lhs, const Circle& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "Circle{center=" << circle.center() << ", r=" << circle.radius() << ", area=" << circle.area() << '}';
    return os;
}

std::istream& operator>>(std::istream& is, Circle& circle) {
    Point center;
    double radius = 0.0;
    is >> center >> radius;
    if (is) {
        circle = Circle(center, radius);
    }
    return is;
}

}  // namespace ds
