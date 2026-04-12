# 11. СТРПО Лаба 5 — CI/CD и автотесты

## Что требует актуальное задание

- тесты только через CMake + `ctest`;
- регистрация через `add_test`;
- GitHub Actions при каждом push;
- минимум две среды / два компилятора;
- Debug и Release;
- падение тестов должно валить workflow.

## Что уже сделано

### Тесты
В `tests/` лежат проверки на:
- `Rect`
- `Barrel`
- `TextWrapper`
- file roundtrip
- большой file roundtrip
- move-семантику `BaseFile`
- `MyString`
- `Matrix`
- `WorkerDb`
- очереди уведомлений
- `BoolArray`

### CMake
В корневом `CMakeLists.txt` тестовые executable добавляются и регистрируются через `add_test`.

### GitHub Actions
Файл:
- `.github/workflows/ci.yml`

Проверяет:
- Linux + GCC
- Windows + MSVC
- Debug и Release

## Что показать на защите

```bash
ctest --test-dir build --output-on-failure
```

И открыть workflow глазами.
