# Примеры для СТРПО-4

В этой папке лежат минимальные примеры для обязательных случаев:

- `segfault.cpp` — обращение по нулевому указателю;
- `leak.cpp` — утечка памяти;
- `ub.cpp` — undefined behaviour через чтение неинициализированной переменной;
- `link_error_decl.hpp` + `link_error_main.cpp` — ошибка линковки.

## Что нужно показать на защите

1. Код каждого примера.
2. Почему ошибка возникает.
3. Каким инструментом она обнаруживается.
4. Обязательную демонстрацию статического анализа (`clang-tidy`).

## Сборка обычных примеров на Windows

```powershell
cmake -S debug_examples -B debug_examples/build -G "Visual Studio 18 2026" -A x64
cmake --build debug_examples/build --config Debug