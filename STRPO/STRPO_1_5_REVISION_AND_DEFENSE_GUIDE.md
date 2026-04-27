# Ревизия и защита СТРПО 1-5

Этот файл нужен как короткий маршрут по первым пяти лабораторным СТРПО.

## СТРПО-1: Git, SSH, приватный репозиторий

Что показать:

```powershell
git status
git remote -v
git branch -a
git log --oneline --graph --decorate --all -20
```

Что сказать: настроен приватный репозиторий, SSH-ключ, `.gitignore`, несколько осмысленных коммитов.

Вопросы: `clone`, `add`, `commit`, `push`, `pull`, `fetch`, `merge`, `.gitignore`, SSH.

## СТРПО-2: GitFlow и Pull Request

Сдавать через отдельный репозиторий `cpp-strpo2-sd3`.

Что показать: `main`, `dev`, `feature/*`, открытый PR `dev -> main`, reviewer/collaborator.

Что сказать: `main` стабильная ветка, `dev` интеграционная, `feature/*` под отдельные задачи. PR нужен для ревью и контролируемого merge.

Важно: PR не закрывать и не мержить до проверки преподавателем.

## СТРПО-3: CMake, static library, find_library, optional dynamic

Обязательная часть:

```powershell
cd STRPO\STRPO_03_cmake_static_library_and_find_library
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Что открыть: `CMakeLists.txt`.

Что объяснить: `add_library`, `add_executable`, `target_include_directories`, `target_link_libraries`, `find_library(... NO_DEFAULT_PATH)`, статическая библиотека.

Необязательная часть для автомата: `optional_dynamic/`. Там есть неявное связывание через `target_link_libraries` и явное связывание через `LoadLibrary/GetProcAddress` или `dlopen/dlsym`.

## СТРПО-4: Debug examples

Что показать: `segfault.cpp`, `leak.cpp`, `ub.cpp`, `link_error_main.cpp`, `CMakeLists.txt`.

Команды:

```powershell
cd STRPO\STRPO_04_debug_examples_sanitizers_clang_tidy
cmake -S . -B build
cmake --build build --config Debug
```

Намеренная ошибка линковки:

```powershell
cmake -S . -B build-link -DSTRPO4_BUILD_LINK_ERROR_DEMO=ON
cmake --build build-link --config Debug
```

Что объяснить: compile error, link error, runtime error, segfault, memory leak, UB, sanitizer, clang-tidy.

## СТРПО-5: CTest + GitHub Actions

Что открыть: `STRPO/STRPO_05_github_actions_ctest_ci/project/CMakeLists.txt` и `.github/workflows/ci.yml`.

Локально:

```powershell
cd STRPO\STRPO_05_github_actions_ctest_ci\project
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Что сказать: тесты регистрируются через `add_test`, запускаются через `ctest`, GitHub Actions гоняет Linux/GCC и Windows/MSVC, Debug и Release. Если тест падает, workflow красный.
