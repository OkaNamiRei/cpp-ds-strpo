#include <iostream>

int main() {
    int* data = new int[10];
    data[0] = 42;
    std::cout << data[0] << '
';
    // delete[] data; // специально пропущено
    return 0;
}
