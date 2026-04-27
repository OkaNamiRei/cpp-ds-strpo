#include <iostream>

int main() {
    int x;
    // Намеренное undefined behaviour: чтение неинициализированной переменной.
    if (x > 0) {
        std::cout << "x is positive" << '\n';
    } else {
        std::cout << "x is not positive" << '\n';
    }
    return 0;
}
