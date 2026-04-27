#include "implicit_cat.hpp"

#include <iostream>

void implicit_cat_print(const char* text) {
    std::cout << "== implicit linking ==\n";
    std::cout << " /\\_/\\\n";
    std::cout << "( o.o )  " << (text ? text : "") << '\n';
    std::cout << " > ^ <\n";
}
