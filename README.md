# DSA Labs Project

This project contains multiple laboratory exercises in C, organized using CMake and a convenient Makefile.

## Prerequisites

- Linux / macOS: `cmake` and `make` installed
- Windows: Use WSL, MSYS2, or MinGW (`mingw32-make`)

C compiler (GCC / Clang) must be installed.

## Build Instructions

### 1. Build all labs

From the project root:

```shell
make build
```

This will:

- Configure CMake in `cmake-build-debug`
- Compile all laboratory executables

### 2. Run a Lab

After building, you can run any lab directly (1-6):

```shell
make lab1
```

Notes:

- If the executable does not exist yet, Makefile will prompt you to `make build` first.
- No rebuild occurs if the executable is already present.

### 3. Clean build artifacts

```shell
make clean
```

This removes the entire `cmake-build-debug` directory.

### 4. Rebuild everything

```shell
make rebuild
```

This is equivalent to `make clean` followed by `make build`.

### 5. List all available Makefile targets

To see all available commands and their description, run:

```shell
make help
```