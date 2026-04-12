# 02. Как устроен репозиторий и как его заливать на GitHub

## Почему один репозиторий

По актуальным требованиям СТРПО лабораторные выполняются параллельно с СД и часть из них можно сдавать на одной кодовой базе. Поэтому выбран **один приватный репозиторий**.

## Структура репозитория

```text
include/ds/               заголовки классов
src/                      реализация
apps/                     демонстрационные main для показа
tests/                    автотесты
assignments/              исходные задания и текст требований
resources/screenshots/    скриншоты сайта и переписки
external/simple_codec/    отдельная внешняя библиотека с исходниками
prebuilt/simple_codec/    собранный бинарный артефакт для find_library
debug_examples/           материалы для СТРПО-4
docker/                   материал для СТРПО-7
coursework_prep/          заготовки под СТРПО-6
optional_dynamic/         необязательный бонус для dynamic libraries
docs/                     шпоры, гайды, карта задания -> код
.github/workflows/        CI
```

## Как создать приватный репозиторий

1. GitHub -> **New repository**.
2. Название любое внятное, например `spbstu-ds-strpo-2026`.
3. Выбрать **Private**.
4. Не ставить галочки на README / `.gitignore`, потому что проект уже существует локально.

## Как залить проект первый раз

```bash
git init
git branch -M main
git add .
git commit -m "init: add combined ds/strpo project"
git remote add origin git@github.com:YOUR_LOGIN/YOUR_REPO.git
git push -u origin main
```

## Какой минимум должен видеть преподаватель

- приватный репозиторий;
- осмысленная история коммитов;
- `.gitignore`;
- ветки `main`, `dev`, `feature/*`;
- Pull Request;
- reviewer;
- workflow в Actions;
- исходные задания в репозитории;
- объяснимую структуру проекта.
