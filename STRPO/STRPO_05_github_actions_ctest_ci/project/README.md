# СД-3: операторы, move, WorkerDb, очереди, BoolArray

## Быстрый запуск

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
.\build\Debug\lab3_demo.exe
```

## Что здесь реализовано

- Перегрузка операторов для `Matrix` и `MyString`.
- Move-семантика на примере `BaseFile`.
- `WorkerDb`: контейнер данных работников.
- `NotificationQueue` и `NotificationPriorityQueue`.
- `BoolArray`: учебный массив булевых значений.

## Что открывать на защите

1. `assignment_original/lab3_original.cpp`.
2. `matrix.*`, `my_string.*` — перегрузка операторов.
3. `base_file.*` — move-семантика.
4. `worker_db.*` — база работников.
5. `notification.*` — обычная и приоритетная очередь.
6. `bool_array.*` — булев массив.
7. `apps/lab3_demo.cpp` и `tests/`.

## Что отвечать

- Copy создаёт копию, move передаёт владение ресурсом.
- `operator[]` в `WorkerDb` нужен, чтобы работать с записью по ключу как с ассоциативным контейнером.
- FIFO выдаёт по порядку добавления, priority queue — по приоритету.
- Перегрузка операторов делает выражения с матрицами/строками естественными.
