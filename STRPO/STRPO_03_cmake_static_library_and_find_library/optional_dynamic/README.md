# СТРПО-3, необязательная часть: динамические библиотеки

Здесь показаны два варианта работы с динамическими библиотеками.

## 1. Неявное связывание

Папка `implicit/` содержит библиотеку `implicit_cat`, которая собирается через:

```cmake
add_library(implicit_cat SHARED implicit/implicit_cat.cpp)
target_link_libraries(dynamic_loader PRIVATE implicit_cat)
```

ОС загрузит эту библиотеку при запуске программы, потому что исполняемый файл связан с ней на этапе линковки.

## 2. Явное связывание

Папка `explicit/` содержит отдельную библиотеку с функцией:

```cpp
extern "C" void cat_print(const char* text);
```

Основной проект не подключает её через `target_link_libraries`. Она грузится руками во время выполнения:

- Windows: `LoadLibrary`, `GetProcAddress`, `FreeLibrary`;
- Linux/macOS: `dlopen`, `dlsym`, `dlclose`.

`extern "C"` нужен, чтобы имя функции не было испорчено C++ name mangling и его можно было найти по строке `cat_print`.

## Windows: команды

```powershell
cd STRPO\STRPO_03_cmake_static_library_and_find_library\optional_dynamic\explicit
cmake -S . -B build
cmake --build build --config Debug

cd ..
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\dynamic_loader.exe .\explicit\build\Debug\explicit_cat.dll
```

Если DLL лежит в другом месте, открой `explicit\build` и передай фактический путь к `explicit_cat.dll`.

## Linux/macOS: команды

```bash
cd STRPO/STRPO_03_cmake_static_library_and_find_library/optional_dynamic/explicit
cmake -S . -B build
cmake --build build

cd ..
cmake -S . -B build
cmake --build build
./build/dynamic_loader ./explicit/build/libexplicit_cat.so
```

На macOS расширение может быть `.dylib`.
