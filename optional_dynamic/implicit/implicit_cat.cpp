#include "implicit_cat.hpp"
#include <iostream>

void implicit_cat_print(const char* text) {
    std::cout << R"( /\_/\
)";
    std::cout << "( o.o )  " << (text ? text : "") << "\n";
    std::cout << " > ^ <\n";
}
