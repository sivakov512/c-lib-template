# C Lib Template

A C library project base with clang-tidy, clangd, and CI pre-configured, unit tests ready to run. Start writing code, not tooling config.

[![Checks](https://github.com/sivakov512/c-lib-template/actions/workflows/checks.yml/badge.svg)](https://github.com/sivakov512/c-lib-template/actions/workflows/checks.yml)
[![Formatting](https://github.com/sivakov512/c-lib-template/actions/workflows/formatting.yml/badge.svg)](https://github.com/sivakov512/c-lib-template/actions/workflows/formatting.yml)

## What's included

- **clang-format, clang-tidy, and clangd work out of the box** — style and analysis config ready, no extra setup needed
- **CI pre-configured** — GitHub Actions for tests, static analysis, and formatting checks
- **Unit tests** — [Unity](https://github.com/ThrowTheSwitch/Unity) via CMake `FetchContent`; tests build and run natively

---

## Requirements

| Tool | Version |
|------|---------|
| CMake | 3.16+ |
| clang-format / clang-tidy / clangd | 18+ |

---

## Quick Start

Click **"Use this template" → "Create a new repository"** on GitHub, then clone your new repo.

Replace `tbd` with your library name in these three places:

- `CMakeLists.txt` — `project(tbd C)` and `add_library(tbd ...)`
- `tests/CMakeLists.txt` — `set(LIBNAME tbd)` and `project(tbd_tests C)`
- `.release-please/config.json` — `"package-name": "tbd"`

Add a `RELEASER_TOKEN` secret to your repository (Settings → Secrets and variables → Actions) — a GitHub token with `contents`, `issues`, and `pull-requests` write permissions. Used by the release workflow.

Run tests:

```bash
make test
```

---

## Project Structure

```
.
├── .github/
│   └── workflows/
│       ├── checks.yml          # tests + clang-tidy
│       ├── formatting.yml      # clang-format check
│       └── release-please.yml  # automated releases
├── .release-please/
│   ├── config.json         # package-name, release type
│   └── manifest.json       # current version
├── include/
│   └── tbd.h               # Public headers
├── src/
│   └── tbd.c               # Library sources
├── tests/
│   ├── test_dummy.c        # Example test
│   └── CMakeLists.txt      # Test build: Unity via FetchContent
├── .clang-format           # LLVM-based style, 85 col limit, 4-space indent
├── .clang-tidy             # Static analysis rules, all warnings as errors
├── CMakeLists.txt          # Library build
└── Makefile                # Convenience targets
```

---

## Makefile Reference

| Target | Description |
|--------|-------------|
| `build` | Configure and build tests |
| `test` | Build and run tests |
| `lint` | Run clang-tidy on all sources |
| `formatting` | Verify formatting with clang-format (dry-run) |
| `check` | `test` + `lint` + `formatting` |
| `clean` | Remove build artifacts |

---

## Adding Tests

Tests live in `tests/`. To add a new test:

1. Create a `test_*.c` file in `tests/`.
2. Add the executable to `tests/CMakeLists.txt` and link it with `unity` and your library.

```cmake
add_executable(my_tests test_my_module.c)

foreach(TESTNAME IN ITEMS my_tests)
    target_link_libraries(${TESTNAME} PRIVATE unity ${LIBNAME})
    set_target_properties(${TESTNAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endforeach()
```

---

## Code Style

### clang-format

Based on **LLVM style**:

- 4-space indentation, 85-column limit
- Tabs → spaces
- Braces: `Attach`
- Sorted includes, blocks preserved

### clang-tidy

Checks enabled: `clang-diagnostic-*`, `clang-analyzer-*`, `bugprone-*`, `performance-*`, `portability-*`, `modernize-*`, `readability-*`, `misc-*`, plus select `google-*` rules. **All warnings are treated as errors.**

**Naming conventions:**

| Context | Convention | Example |
|---------|-----------|---------|
| C functions | `snake_case` | `lib_init` |
| C structs / typedefs | `snake_case_t` | `ctx_t` |
| C++ classes / enums | `CamelCase` | `MyClass` |
| C++ methods | `snake_case` | `process` |
| C++ members | `snake_case_` | `retry_count_` |
| Class constants | `kCamelCase` | `kMaxRetries` |
| Enum values | `UPPER_CASE` | `STATE_IDLE` |
| Macros & global constants | `UPPER_CASE` | `MAX_SIZE` |
| Global variables | `g_` prefix | `g_instance` |
| Namespaces | `lower_case` | `utils` |

See [`.clang-tidy`](.clang-tidy) for the complete configuration.
