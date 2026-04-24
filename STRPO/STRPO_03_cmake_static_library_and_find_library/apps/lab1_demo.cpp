#include "ds/barrel.hpp"
#include "ds/matrix.hpp"
#include "ds/my_string.hpp"
#include "ds/rect.hpp"
#include "ds/text_wrapper.hpp"

#include <iostream>

int main() {
    using namespace ds;

    std::cout << "=== Rect ===\n";
    Rect r1(1, 5, 6, 2);
    Rect r2 = r1;
    r2.move(2, -1);
    r2.inflate(1, 2);
    std::cout << r1 << "\n" << r2 << "\n\n";

    std::cout << "=== Barrel ===\n";
    Barrel spirit = Barrel::spirit_barrel(9.0, 9.0, 0.96);
    Barrel water = Barrel::water_barrel(10.0, 10.0);
    int iteration = Barrel::iteration_until_fraction_below(spirit, water, 1.0, 0.5);
    std::cout << "iteration until below 50% = " << iteration << "\n\n";

    std::cout << "=== Matrix / Fibonacci ===\n";
    Matrix identity(3);
    std::cout << "matrix(0,0) = " << identity.get(0, 0) << "\n";
    std::cout << "fib(10) = " << fibonacci_matrix(10) << "\n\n";

    std::cout << "=== MyString + TextWrapper ===\n";
    MyString text("this is a wrapped line example for the first lab");
    TextWrapper wrapper(text, 12);
    wrapper.print_wrapped(std::cout);
    std::cout << "\nlines = " << wrapper.count_lines() << "\n";
    return 0;
}
