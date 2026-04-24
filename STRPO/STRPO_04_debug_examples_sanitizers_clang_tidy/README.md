# Примеры для СТРПО-4

В этой папке лежат минимальные примеры для обязательных случаев:

- `segfault.cpp` — обращение по нулевому указателю;
- `leak.cpp` — утечка памяти;
- `ub.cpp` — undefined behaviour;
- `link_error_decl.hpp` + `link_error_main.cpp` — ошибка линковки.

## Как показывать

### Linux / WSL
```bash
g++ -g -O0 segfault.cpp -o segfault
./segfault

g++ -g -O0 -fsanitize=address leak.cpp -o leak
./leak

g++ -g -O0 -fsanitize=undefined ub.cpp -o ub
./ub

g++ -g -O0 link_error_main.cpp -o link_error
```

### Что объяснять
- почему именно эта ошибка возникает;
- каким инструментом она ловится;
- что нужно исправить в коде.


## Коротко для защиты
Показываешь `segfault.cpp`, `leak.cpp`, `link_error_main.cpp`, `ub.cpp`, сборку через CMake и запуск clang-tidy. Важно объяснить не только ошибку, но и каким инструментом её находишь.
