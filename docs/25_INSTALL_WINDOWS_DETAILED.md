# 25. Установка на Windows — совсем пошагово

## Git
1. Скачать Git for Windows.
2. Во время установки можно оставлять дефолтные настройки.
3. После установки открыть Git Bash и ввести `git --version`.

## Visual Studio
1. Скачать Visual Studio Community.
2. Авторизоваться учёткой Microsoft, если попросит.
3. В Installer выбрать workload `Desktop development with C++`.
4. Установить.
5. После установки открыть VS и убедиться, что проект на CMake открывается как Folder.

## CMake и Ninja
Если они уже приехали вместе с Visual Studio, отдельно можно не ставить. Проверка через терминал:

```bash
cmake --version
ninja --version
```

## Docker Desktop
Ставить только если нужен Docker.

## GitHub
1. Зарегистрировать аккаунт.
2. Войти через браузер.
3. Добавить SSH-ключ.
