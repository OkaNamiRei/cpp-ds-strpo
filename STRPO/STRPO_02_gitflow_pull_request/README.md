# СТРПО-2: GitFlow и Pull Request

Основная сдача этой лабы должна быть через отдельный приватный GitHub-репозиторий `cpp-strpo2-sd3`, а не через этот большой архив. Здесь лежит локальная копия кодовой базы СД-3 в `code_base_sd3/`, чтобы было из чего восстановиться.

## Что показать преподавателю
1. Отдельный приватный репозиторий `cpp-strpo2-sd3`.
2. Ветки `main`, `dev`, `feature/*`.
3. Pull Request `dev -> main`.
4. Reviewer/collaborator преподавателя.
5. Что код собирается и тестируется.

## Проверка локальной копии
```powershell
cd code_base_sd3
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```
