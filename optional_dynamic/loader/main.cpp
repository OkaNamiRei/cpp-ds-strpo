#include <iostream>
#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

int main() {
#if defined(_WIN32)
    HMODULE lib = LoadLibraryA("explicit_cat.dll");
    if (!lib) {
        std::cerr << "Cannot load explicit_cat.dll\n";
        return 1;
    }
    using func_t = void(*)(const char*);
    auto func = reinterpret_cast<func_t>(GetProcAddress(lib, "cat_print"));
    if (!func) {
        std::cerr << "Cannot resolve cat_print\n";
        FreeLibrary(lib);
        return 1;
    }
    func("loaded explicitly");
    FreeLibrary(lib);
#else
    void* lib = dlopen("./libexplicit_cat.so", RTLD_LAZY);
    if (!lib) {
        std::cerr << "Cannot load libexplicit_cat.so\n";
        return 1;
    }
    using func_t = void(*)(const char*);
    auto func = reinterpret_cast<func_t>(dlsym(lib, "cat_print"));
    if (!func) {
        std::cerr << "Cannot resolve cat_print\n";
        dlclose(lib);
        return 1;
    }
    func("loaded explicitly");
    dlclose(lib);
#endif
    return 0;
}
