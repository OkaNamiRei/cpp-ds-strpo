# 08. СТРПО Лаба 2 — ветки и Pull Request

## Что требует актуальное задание

- приватный репозиторий;
- `main` как стабильная ветка;
- `dev` как интеграционная;
- отдельные `feature/*`-ветки;
- прямые коммиты в `main` запрещены;
- Pull Request из `dev` в `main`;
- преподаватель `Stasychbr` должен быть добавлен как collaborator/reviewer.

## Как логично разбить этот проект

- `feature/sd1-core`
- `feature/sd2-files`
- `feature/sd3-operators`
- `feature/sd3-db-and-queues`
- `feature/build-tests-ci`
- `feature/docs`

## Рабочий сценарий

```bash
git switch -c dev
git push -u origin dev
git switch -c feature/sd1-core
# работа
# commit
# push
# PR feature/sd1-core -> dev
```

После нескольких feature-веток:
- PR `dev -> main`;
- назначаешь reviewer;
- после замечаний вносишь правки;
- делаешь merge.

## Что важно сказать

Для СД устный опрос по коду всё равно остаётся. СТРПО-2 закрывает организацию работы с репозиторием, а не заменяет объяснение кода.
