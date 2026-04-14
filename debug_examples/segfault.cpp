#include <iostream>

int main() {
    std::cout << "About to dereference a null pointer..." << std::endl;
    int* p = nullptr;
    std::cout << *p << std::endl;
    return 0;
}