# СД-1: ООП, Rect, Barrel, Matrix, MyString, TextWrapper

## Быстрый запуск

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
.\build\Debug\lab1_demo.exe
```

## Что здесь реализовано

- `Rect`: конструкторы, копирование, `move`, `inflate`, операции с прямоугольниками.
- `Barrel`: расчёт концентрации без `%`, через десятичные доли.
- `Matrix`: хранение матрицы и Fibonacci через матричный подход.
- `MyString` и `TextWrapper`: собственная строка и перенос текста.

## Что открывать на защите

1. `assignment_original/lab1_original.cpp` — исходное задание.
2. `include/ds/rect.hpp`, `src/rect.cpp` — конструкторы, копирование, методы.
3. `include/ds/barrel.hpp`, `src/barrel.cpp` — расчёт концентрации.
4. `include/ds/matrix.hpp`, `src/matrix.cpp` — матрица и Fibonacci.
5. `apps/lab1_demo.cpp` — общий сценарий показа.
6. `tests/` — автопроверки.

## Что отвечать

- `Rect r2 = r1` вызывает конструктор копирования, потому что новый объект создаётся по уже существующему.
- Конструкторы: по умолчанию, параметризованный, копирования, перемещения, конвертирующий.
- Инкапсуляция — скрытие реализации за публичным интерфейсом.
- Этапы сборки: препроцессинг, компиляция, линковка.
- Линковщик различает перегруженные методы по сигнатурам и name mangling.
