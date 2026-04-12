# 03. Как открыть, собрать, запустить и показать проект

## Вариант A. Через Visual Studio

1. `File -> Open -> Folder`.
2. Выбрать корень репозитория.
3. Подождать, пока Visual Studio увидит `CMakeLists.txt`.
4. Выбрать конфигурацию `x64-Debug`.
5. Собрать проект.
6. Запустить по очереди `lab1_demo`, `lab2_demo`, `lab3_demo`.
7. Открыть встроенный терминал и выполнить `ctest --test-dir build --output-on-failure`.

## Вариант B. Через терминал

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Что показывать по СД

### СД-1
- `apps/lab1_demo.cpp`
- `Rect`, `Barrel`, `Matrix`, `MyString`, `TextWrapper`
- тесты `test_rect_*`, `test_barrel`, `test_text_wrapper`

### СД-2
- `apps/lab2_demo.cpp`
- `BaseFile`, `Base32File`, `RleFile`, `IFile`, композиционные классы
- `test_file_roundtrip`, `test_large_file_roundtrip`, `test_base_file_move`

### СД-3
- `apps/lab3_demo.cpp`
- строки, матрицы, БД работников, уведомления, очереди, `BoolArray`
- тесты `test_my_string_lab3`, `test_matrix_lab3`, `test_worker_db`, `test_notification_queues`, `test_bool_array`

## Что показывать по СТРПО

### СТРПО-1
- приватный репозиторий
- `.gitignore`
- история коммитов
- SSH-подключение или другой способ аутентификации

### СТРПО-2
- ветки `main`, `dev`, `feature/*`
- Pull Request
- reviewer `Stasychbr`

### СТРПО-3
- `CMakeLists.txt`
- сборка только через CMake
- отдельный каталог `build`
- `external/simple_codec/`
- `prebuilt/simple_codec/`
- при желании `optional_dynamic/`

### СТРПО-4
- `debug_examples/`
- показать хотя бы один кейс на санитайзере и один кейс как линковочную ошибку

### СТРПО-5
- `tests/`
- `add_test` в CMake
- `.github/workflows/ci.yml`

### СТРПО-6
- пока только `coursework_prep/`, потому что без курсовой это не закрывается физически

### СТРПО-7
- папку `docker/`
- `Dockerfile`
- команды `docker build` / `docker run`
