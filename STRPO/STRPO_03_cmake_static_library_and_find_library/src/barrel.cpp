#include "ds/barrel.hpp"

#include <algorithm>
#include <stdexcept>

namespace ds {

Barrel::Barrel() : capacity_liters_(0.0), liters_(0.0), spirit_liters_(0.0) {}

Barrel::Barrel(double capacity_liters, double initial_liters, double spirit_fraction)
    : capacity_liters_(capacity_liters < 0.0 ? 0.0 : capacity_liters), liters_(0.0), spirit_liters_(0.0) {
    fill(initial_liters, spirit_fraction);
}

Barrel Barrel::spirit_barrel(double capacity_liters, double fill_liters, double strength) {
    return Barrel(capacity_liters, fill_liters, strength);
}

Barrel Barrel::water_barrel(double capacity_liters, double fill_liters) {
    return Barrel(capacity_liters, fill_liters, 0.0);
}

double Barrel::capacity() const { return capacity_liters_; }
double Barrel::liters() const { return liters_; }
double Barrel::spirit_liters() const { return spirit_liters_; }
double Barrel::water_liters() const { return liters_ - spirit_liters_; }
double Barrel::free_space() const { return capacity_liters_ - liters_; }
bool Barrel::empty() const { return liters_ <= 1e-12; }

double Barrel::spirit_fraction() const {
    if (empty()) return 0.0;
    return spirit_liters_ / liters_;
}

void Barrel::fill(double liters, double spirit_fraction) {
    if (liters <= 0.0) return;
    if (spirit_fraction < 0.0 || spirit_fraction > 1.0) {
        throw std::invalid_argument("spirit fraction must be in [0, 1]");
    }
    double added = std::min(liters, capacity_liters_ - liters_);
    liters_ += added;
    spirit_liters_ += added * spirit_fraction;
}

double Barrel::pour_to(Barrel& other, double liters) {
    if (liters <= 0.0 || this == &other || empty()) return 0.0;
    double moved = std::min(liters, liters_);
    double moved_spirit = moved * spirit_fraction();

    liters_ -= moved;
    spirit_liters_ -= moved_spirit;
    if (liters_ < 1e-12) {
        liters_ = 0.0;
        spirit_liters_ = 0.0;
    }

    double other_old_fraction = other.spirit_fraction();
    other.liters_ += moved;
    other.spirit_liters_ += moved_spirit;
    if (other.liters_ > other.capacity_liters_) {
        double overflow = other.liters_ - other.capacity_liters_;
        other.liters_ -= overflow;
        other.spirit_liters_ -= overflow * other_old_fraction;
        if (other.spirit_liters_ < 0.0) other.spirit_liters_ = 0.0;
    }
    return moved;
}

int Barrel::iteration_until_fraction_below(Barrel first, Barrel second,
                                           double mug_liters,
                                           double threshold_fraction) {
    if (mug_liters <= 0.0) throw std::invalid_argument("mug liters must be positive");
    if (threshold_fraction < 0.0 || threshold_fraction > 1.0) {
        throw std::invalid_argument("threshold fraction must be in [0, 1]");
    }
    int iteration = 0;
    while (first.spirit_fraction() >= threshold_fraction) {
        ++iteration;
        first.pour_to(second, mug_liters);
        second.pour_to(first, mug_liters);
        if (iteration > 1000000) {
            throw std::runtime_error("too many iterations in barrel simulation");
        }
    }
    return iteration;
}

}  // namespace ds
