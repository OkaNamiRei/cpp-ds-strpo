# СТРПО-3: CMake, статическая библиотека, внешний артефакт через find_library

## Обычная сборка
```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Сборка с prebuilt-библиотекой
```powershell
cmake -S . -B build-prebuilt -DDS_USE_PREBUILT_CODEC=ON
cmake --build build-prebuilt --config Debug
```

## Что сказать
`ds_core` — внутренняя статическая библиотека проекта. `find_library` ищет уже собранный внешний `.lib/.a` артефакт. Это отличается от `add_subdirectory`, где библиотека собирается из исходников вместе с проектом.
