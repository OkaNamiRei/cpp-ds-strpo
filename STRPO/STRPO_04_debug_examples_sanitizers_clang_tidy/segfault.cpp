#include <iostream>

int main() {
    int* p = nullptr;
    std::cout << "About to dereference a null pointer..." << '\n';
    std::cout << *p << '\n'; // намеренный segfault / access violation
    return 0;
}
