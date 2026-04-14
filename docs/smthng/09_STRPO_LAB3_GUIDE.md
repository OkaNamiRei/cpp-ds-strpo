# 09. СТРПО Лаба 3 — CMake, статические библиотеки и бонус про dynamic libraries

## Что требует обязательная часть

### Этап 1
- главный `CMakeLists.txt`;
- сборка только через `cmake`;
- отдельный каталог `build`.

### Этап 2
- часть функциональности вынесена во внутреннюю статическую библиотеку;
- используются `add_library`, `target_include_directories`, `target_link_libraries`;
- `file(GLOB ...)` не используется.

### Этап 3
- отдельная библиотека лежит отдельно;
- основной проект не тащит её исходники;
- библиотека находится через `find_library(PATHS ... NO_DEFAULT_PATH)`;
- при отсутствии библиотеки сборка падает с понятной ошибкой.

## Как это сделано в проекте

### Внутренняя библиотека
`ds_core` в корневом `CMakeLists.txt`.

### Внешняя библиотека
- исходники: `external/simple_codec/`
- бинарник: `prebuilt/simple_codec/`
- подключение: опция `DS_USE_PREBUILT_CODEC=ON`

## Команды показа

```bash
cmake -S . -B build
cmake --build build
```

```bash
cmake -S . -B build-prebuilt -DDS_USE_PREBUILT_CODEC=ON
cmake --build build-prebuilt
```

## Необязательный этап про shared libraries

Актуальные требования теперь содержат ещё и **необязательный** этап 4 про dynamic libraries. Он не обязателен для обычной сдачи, но под него оставлен отдельный комплект:

- `optional_dynamic/`

Там есть:
- пример неявного связывания;
- пример явной загрузки библиотеки во время выполнения;
- функция `extern "C" void cat_print(const char*)`.
