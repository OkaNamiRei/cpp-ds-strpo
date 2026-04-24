#include "ds/barrel.hpp"

#include <cassert>

int main() {
    using namespace ds;
    Barrel spirit = Barrel::spirit_barrel(9.0, 9.0, 0.96);
    Barrel water = Barrel::water_barrel(10.0, 10.0);
    int iteration = Barrel::iteration_until_fraction_below(spirit, water, 1.0, 0.5);
    assert(iteration > 0);
    Barrel a = Barrel::spirit_barrel(5.0, 4.0, 0.5);
    Barrel b = Barrel::water_barrel(5.0, 1.0);
    double moved = a.pour_to(b, 2.0);
    assert(moved == 2.0);
    assert(a.liters() == 2.0);
    assert(b.liters() == 3.0);
    return 0;
}
