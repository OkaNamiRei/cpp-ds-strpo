# 10. СТРПО Лаба 4 — отладка и анализ ошибок

## Что требует актуальное задание

Нужно показать минимальные примеры для:
1. segmentation fault
2. memory leak
3. link error
4. undefined behaviour

И обязательно показать **статический анализ**.

## Где лежат примеры

- `debug_examples/segfault.cpp`
- `debug_examples/leak.cpp`
- `debug_examples/link_error_decl.hpp`
- `debug_examples/link_error_main.cpp`
- `debug_examples/ub.cpp`
- `.clang-tidy`

## Как показать динамический анализ

### Segfault
```bash
g++ -g debug_examples/segfault.cpp -o segfault.out
./segfault.out
```

### Leak / UB
```bash
g++ -g -fsanitize=address,undefined -fno-omit-frame-pointer debug_examples/leak.cpp -o leak.out
./leak.out

g++ -g -fsanitize=address,undefined -fno-omit-frame-pointer debug_examples/ub.cpp -o ub.out
./ub.out
```

### Link error
```bash
g++ debug_examples/link_error_main.cpp -o link_error.out
```

## Как показать статический анализ

Если у тебя установлен `clang-tidy`:

```bash
clang-tidy debug_examples/segfault.cpp -- -std=c++17
clang-tidy src/*.cpp -- -Iinclude -std=c++17
```

Если на твоём ПК его пока нет, ставишь и показываешь хотя бы запуск по одному файлу. На моей стороне в контейнере `clang-tidy` не был установлен, поэтому эта часть подготовлена структурно, но не запускалась здесь.
