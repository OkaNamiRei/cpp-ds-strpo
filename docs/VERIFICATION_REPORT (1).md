# Verification report after full recheck

## Inputs considered

- `lab1.zip`, `lab2.zip`, `lab3.zip` — original SD assignments.
- `ssh_guide.md` — guide for SSH.
- `labs.md` — old STRPO requirements.
- `labs_final_complete.md` — **current** STRPO requirements.
- screenshots from the site and Telegram messages.

## What was changed in the bundle

- Added the **current** STRPO requirements to `repo/assignments/strpo/labs_final_complete.md`.
- Kept the old STRPO requirements in `repo/assignments/strpo/archive_old/labs_initial.md`.
- Added guides for **СТРПО-6** and **СТРПО-7**.
- Added `coursework_prep/` templates for the future coursework tracker lab.
- Added `docker/` demo for lab 7.
- Added `optional_dynamic/` for the optional dynamic-library stage of STRPO-3.
- Cleaned build artifacts out of the final repo snapshot.
- Updated `README.md`, `CMakePresets.json`, `.gitignore`, and all main guides.
- Rebuilt the master Word guide and visually checked its rendered pages.

## What was verified locally

### 1. Main build and tests
Commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Result:
- build passed
- **14 / 14 tests passed**

### 2. Build with prebuilt external library
Commands:

```bash
cmake -S . -B build-prebuilt -DDS_USE_PREBUILT_CODEC=ON
cmake --build build-prebuilt
```

Result:
- configuration passed
- build passed

### 3. ASan/UBSan build and tests
Commands:

```bash
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer'   -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'   -DCMAKE_SHARED_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build build-asan -j1
ctest --test-dir build-asan --output-on-failure
```

Result:
- build passed
- **14 / 14 tests passed under ASan/UBSan**

### 4. Optional dynamic-library demo
Commands:

```bash
cmake -S optional_dynamic -B optional_dynamic/build
cmake --build optional_dynamic/build -j1
```

Result:
- build passed

### 5. Docker demo source sanity check
Command:

```bash
g++ -std=c++17 docker/ascii_cat.cpp -o ascii_cat
./ascii_cat
```

Result:
- compiled
- ran successfully

### 6. Master guide DOCX QA
File:
- `repo/docs/MASTER_GUIDE.docx`

Result:
- rendered to PNG successfully
- pages inspected visually
- formatting accepted

## Important honest notes

- **СТРПО-1** and **СТРПО-2** cannot be fully “executed” inside this archive alone, because the final steps require your own GitHub account, private repository, branches, pull requests, collaborator/reviewer, and visible history on the remote service.
- **СТРПО-6** cannot be fully completed before the coursework exists. The bundle contains prepared templates and instructions only.
- **СТРПО-7** was prepared fully as files and commands, but Docker itself was not run inside this environment because Docker is unavailable here.
- `clang-tidy` config is included for STRPO-4, but `clang-tidy` itself was not installed in this environment, so that part must be run on your machine.

## Recommended entry points

1. `repo/README.md`
2. `repo/docs/00_MASTER_PLAN.md`
3. `repo/docs/20_UPDATED_REQUIREMENTS_AND_DECISIONS.md`
4. `repo/docs/26_PRE_DEFENSE_CHECKLIST.md`
5. `repo/docs/MASTER_GUIDE.docx`
