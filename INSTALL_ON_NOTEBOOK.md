# Что поставить на ноут перед показом

## Обязательно

1. Git for Windows.
2. Visual Studio Community с workload `Desktop development with C++`.
3. CMake tools for Windows и Windows SDK внутри Visual Studio Installer.
4. Доступ к GitHub.

## Проверки

```powershell
git --version
cmake --version
ssh -T git@github.com
```

## Для Docker-лабы, если будешь показывать

1. Docker Desktop.
2. Запустить Docker Desktop перед командами.
3. Проверить:

```powershell
docker --version
docker run hello-world
```

## Главная команда проверки CMake-проектов на Windows

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Если забыть `-C Debug`, CTest опять устроит цирк с `Test not available without configuration`. Мы уже этот аттракцион видели, хватит.
