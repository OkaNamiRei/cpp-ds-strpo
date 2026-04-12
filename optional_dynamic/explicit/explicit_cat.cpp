#include <iostream>
extern "C" void cat_print(const char* text) {
    std::cout << R"( /\_/\
)";
    std::cout << "( o.o )  " << (text ? text : "") << "\n";
    std::cout << " > ^ <\n";
}
