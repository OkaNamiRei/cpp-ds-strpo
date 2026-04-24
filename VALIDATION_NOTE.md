# Validation note

Папки собраны как самостоятельные CMake-проекты. В этой среде я не стал оставлять `build/`-артефакты в архиве. На Windows проверять так:

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Важный момент: для Visual Studio/Windows нужен `-C Debug`, иначе CTest пишет `Test not available without configuration`.
