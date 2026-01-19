# Data Structures and Algorithms UTM

## Prerequisites

To build and run this project, you need the following tools installed:

- CMake ≥ 4.1
- C compiler
  - Linux: gcc or clang
  - Windows: MinGW-w64 or Microsoft Visual C++ (MSVC)
- Build system
  - Ninja (recommended) or
  - Make (Linux) / MSBuild (Windows)

## Quick Start (Linux)

Create a build directory

```sh
mkdir cmake-build-debug
cd cmake-build-debug
```
Configure the project

```sh
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Build

```sh
cmake --build .
```

Run the Program

```sh
./dsa
```

## Quick Start (Windows)

### Option 1: Using MinGW-w64 (Command Prompt or PowerShell)

Create a build directory

```sh
mkdir cmake-build-debug
cd cmake-build-debug
```
Configure the project

```sh
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

Build

```sh
cmake --build .
```

### Option 2: Using Visual Studio (MSVC)

Create a build directory

```sh
mkdir cmake-build-debug
cd cmake-build-debug
```
Configure the project

```sh
cmake .. -G "Visual Studio 17 2022"
```

Build

```sh
cmake --build . --config Debug
```

Run the Program

```sh
dsa.exe
```

## Notes

- The project uses out-of-source builds (recommended CMake practice).
- If CMake reports “ninja: no work to do”, the project is already up to date.
- To clean the build, simply delete the cmake-build-debug directory and rebuild.