#include "implicit_cat.hpp"

#include <iostream>
#include <string>

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

using cat_print_t = void (*)(const char*);

int main(int argc, char** argv) {
    implicit_cat_print("loaded implicitly");

    std::string library_path;
    if (argc > 1) {
        library_path = argv[1];
    } else {
#if defined(_WIN32)
        library_path = "explicit_cat.dll";
#elif defined(__APPLE__)
        library_path = "./libexplicit_cat.dylib";
#else
        library_path = "./libexplicit_cat.so";
#endif
    }

#if defined(_WIN32)
    HMODULE handle = LoadLibraryA(library_path.c_str());
    if (!handle) {
        std::cerr << "Cannot load library: " << library_path << '\n';
        return 1;
    }
    auto cat_print = reinterpret_cast<cat_print_t>(GetProcAddress(handle, "cat_print"));
    if (!cat_print) {
        std::cerr << "Cannot find function cat_print" << '\n';
        FreeLibrary(handle);
        return 2;
    }
    cat_print("loaded explicitly");
    FreeLibrary(handle);
#else
    void* handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << library_path << " -> " << dlerror() << '\n';
        return 1;
    }
    auto cat_print = reinterpret_cast<cat_print_t>(dlsym(handle, "cat_print"));
    if (!cat_print) {
        std::cerr << "Cannot find function cat_print" << '\n';
        dlclose(handle);
        return 2;
    }
    cat_print("loaded explicitly");
    dlclose(handle);
#endif
    return 0;
}
