# Единый репозиторий для лабораторных по СД и СТРПО

Этот проект собран как **одна кодовая база** для лабораторных по **«Структурам данных»** и **«Современным технологиям разработки ПО»**.

Смысл простой и утомительно логичный:
- код по СД 1-3 лежит в одном месте;
- СТРПО 1, 2, 3 и 5 опираются на эту же базу;
- СТРПО 4 вынесена в `debug_examples/`;
- СТРПО 6 пока подготовлена как шаблонный комплект под будущую курсовую;
- СТРПО 7 подготовлена как отдельный Docker-демо-набор.

> В папке `assignments/strpo/` лежит **актуальная** версия требований `labs_final_complete.md`. Старый вариант сохранён в `archive_old/`.

## Что закрыто кодом

### СД
- **Лаба 1**: `Rect`, `Barrel`, `Matrix`, `MyString`, `TextWrapper`, функции и тесты.
- **Лаба 2**: `BaseFile`, `Base32File`, `RleFile`, `IFile`, композиционные обёртки, тесты.
- **Лаба 3**: перегрузка операторов, move-семантика, `WorkerDb`, уведомления, очереди, `BoolArray`.

### СТРПО
- **Лаба 1**: приватный репозиторий, `.gitignore`, SSH-гайд, история осмысленных коммитов.
- **Лаба 2**: `main` / `dev` / `feature/*`, Pull Request, reviewer, GitFlow-раскладка.
- **Лаба 3**: CMake, внутренняя статическая библиотека, внешний бинарный артефакт через `find_library`.
- **Лаба 4**: отдельные минимальные примеры segfault / leak / link error / UB + `.clang-tidy`.
- **Лаба 5**: `ctest` + GitHub Actions.
- **Лаба 6**: подготовлены шаблоны для issues, Kanban, веток, PR и связи с курсовой. Полностью закрывается только после появления самой курсовой.
- **Лаба 7**: отдельная папка `docker/` с Dockerfile и мини-демо.

## Где лежат исходные задания

- `assignments/sd/original/` - оригинальные `lab1.cpp`, `lab2.cpp`, `lab3.cpp`.
- `assignments/strpo/labs_final_complete.md` - актуальные требования по СТРПО.
- `assignments/strpo/archive_old/labs_initial.md` - старая версия требований.
- `assignments/strpo/ssh_guide.md` - SSH-инструкция.
- `resources/screenshots/` - скриншоты сайта и переписки.

## Что открыть в первую очередь

1. `docs/00_MASTER_PLAN.md`
2. `docs/01_INSTALL_AND_TOOLS.md`
3. `docs/02_REPO_STRUCTURE_AND_GITHUB.md`
4. `docs/03_OPEN_BUILD_RUN_SHOW.md`
5. `docs/20_UPDATED_REQUIREMENTS_AND_DECISIONS.md`

## Быстрый запуск

### Обычная сборка

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Через presets

```bash
cmake --preset default
cmake --build --preset default
ctest --preset default
```

### Внешняя библиотека через `find_library`

```bash
cmake -S . -B build-prebuilt -DDS_USE_PREBUILT_CODEC=ON
cmake --build build-prebuilt
```

### Sanitzer-проверка

```bash
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug       -DCMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer'       -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

## Что показывать на защите

```bash
./build/lab1_demo
./build/lab2_demo
./build/lab3_demo
ctest --test-dir build --output-on-failure
```
