# 01. Установка программ и окружения

## Базовый комплект для Windows

### 1. Git for Windows
Нужен для:
- `git` в терминале;
- SSH-ключей;
- push/pull/branch/merge.

После установки проверь:

```bash
git --version
ssh -V
```

### 2. Visual Studio Community 2022
При установке выбери workload:
- **Desktop development with C++**

Желательно, чтобы были отмечены:
- MSVC toolset;
- CMake tools for Windows;
- Windows SDK.

### 3. GitHub аккаунт
Нужен для СТРПО-1/2/5/6.

## Желательно поставить ещё

### 4. CMake
Если Visual Studio не подхватила свой, поставь отдельно.

Проверка:

```bash
cmake --version
```

### 5. Ninja
Полезен для CMake presets и быстрой сборки.

Проверка:

```bash
ninja --version
```

### 6. WSL + Ubuntu
Полезно для:
- `g++`;
- `gdb`;
- sanitizers;
- поведения, похожего на Linux.

### 7. Docker Desktop
Нужно только если будешь показывать СТРПО-7.

Проверка:

```bash
docker --version
docker run hello-world
```

## Что ещё полезно

- 7-Zip для распаковки архивов;
- любой удобный терминал;
- браузер с входом в GitHub.

## Где хранится SSH-ключ

### Windows
```text
C:/Users/<username>/.ssh/
```

### WSL / Linux
```text
/home/<username>/.ssh/
```

## Что использовать для поиска утечек и ошибок

### Минимум
- AddressSanitizer
- UndefinedBehaviorSanitizer

### Дополнительно
- Visual Studio debugger
- Valgrind в WSL/Linux
- clang-tidy для статического анализа

## Минимальная самопроверка после установки

```bash
git --version
cmake --version
```

Для WSL:

```bash
g++ --version
gdb --version
```

Для Docker:

```bash
docker --version
```
