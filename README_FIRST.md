# Разделённый архив лабораторных СД + СТРПО

Я разложил большой репозиторий по отдельным папкам, чтобы каждую лабу можно было открыть и показать отдельно. Да, пришлось распилить монолит, потому что препод уже тонко намекнул, что большой репозиторий с кучей всего его не радует. Невероятно, но бюрократия иногда права.

## Что внутри

### `SD/`
Каждая лабораторная по структурам данных лежит отдельно и собирается сама по себе:

- `SD_01_oop_basics_rect_barrel_matrix_string`
- `SD_02_file_abstractions_base32_rle`
- `SD_03_operators_move_workerdb_queues_boolarray`
- `SD_04_circle_doubly_linked_list`

В каждой папке есть `CMakeLists.txt`, `include/`, `src/`, `apps/`, `tests/`, `assignment_original/`, `guide/`, `README.md`.

### `STRPO/`
СТРПО разложено по смыслу:

- `STRPO_01_git_private_repo_ssh_commits`
- `STRPO_02_gitflow_pull_request`
- `STRPO_03_cmake_static_library_and_find_library`
- `STRPO_04_debug_examples_sanitizers_clang_tidy`
- `STRPO_05_github_actions_ctest_ci`
- `STRPO_06_coursework_tracker_preparation`
- `STRPO_07_docker_container`

## Как проверять СД-лабы

В любой папке `SD/...`:

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
.\build\Debug\labN_demo.exe
```

где `N` — номер лабы.

На Linux/Ninja/обычном Make:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/labN_demo
```

## Что завтра сдавать первым

1. СТРПО-1 и СТРПО-2 через отдельный приватный репозиторий `cpp-strpo2-sd3`.
2. Потом СД-3 по той же кодовой базе.
3. Остальные СД-лабы показывать очно из папок `SD/`, если останется время или если попросят.
4. СТРПО-3/4/5/7 — как запас/допы, не пихать первыми.

## Обновление ревизии СТРПО 1-5

Добавлена ревизия первых лабораторных СТРПО:

- `STRPO/STRPO_1_5_REVISION_AND_DEFENSE_GUIDE.md` — что открывать и что говорить на защите;
- `STRPO/STRPO_03_cmake_static_library_and_find_library/optional_dynamic/` — необязательная часть с динамическими библиотеками;
- `STRPO/STRPO_04_debug_examples_sanitizers_clang_tidy/CMakeLists.txt` — сборка примеров отладки;
- `.github/workflows/ci.yml` — root workflow для проверки СТРПО-5 через GitHub Actions.
