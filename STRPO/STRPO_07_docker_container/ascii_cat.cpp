#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string text = argc > 1 ? argv[1] : "docker works";
    std::cout << R"( /\_/\
)";
    std::cout << "( o.o )  " << text << "\n";
    std::cout << " > ^ <\n";
    return 0;
}
