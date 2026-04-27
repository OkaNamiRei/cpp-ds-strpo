#include <iostream>
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

int main() {
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    int* data = new int[10];
    data[0] = 42;
    std::cout << "data[0] = " << data[0] << '\n';
    // delete[] data; // специально пропущено: демонстрация утечки памяти
    return 0;
}
