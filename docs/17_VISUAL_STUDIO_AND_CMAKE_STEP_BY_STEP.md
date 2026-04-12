# 17. Visual Studio + CMake: пошагово

## Открытие проекта

1. Запусти Visual Studio Community 2022.
2. Выбери `File -> Open -> Folder`.
3. Укажи корень репозитория.
4. Подожди, пока Visual Studio прочитает `CMakeLists.txt`.

## Сборка

1. Вверху выбери конфигурацию `x64-Debug`.
2. Нажми `Build All`.
3. Проверь, что собраны `lab1_demo`, `lab2_demo`, `lab3_demo` и тесты.

## Запуск

- Можно запускать demo targets отдельно.
- Для тестов можно либо запускать targets руками, либо открыть терминал в корне проекта и выполнить:

```bash
ctest --test-dir build --output-on-failure
```

## Что показать преподавателю прямо из Visual Studio

- дерево проекта;
- `CMakeLists.txt`;
- один из header/source-файлов;
- demo-приложение;
- тесты;
- при необходимости `debug_examples/`.
