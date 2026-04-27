#include <iostream>

#if defined(_WIN32)
  #define EXPLICIT_CAT_API extern "C" __declspec(dllexport)
#else
  #define EXPLICIT_CAT_API extern "C"
#endif

EXPLICIT_CAT_API void cat_print(const char* text) {
    std::cout << "== explicit linking ==\n";
    std::cout << " /\\_/\\\n";
    std::cout << "( o.o )  " << (text ? text : "") << '\n';
    std::cout << " > ^ <\n";
}
