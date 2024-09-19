# CMake

## Introduction

[CMakePresets.json](CMakePresets.json) defines various debug and release configurations, including the compiler flags.

Using Ninja with cmake for faster builds. CmakePreset.json is used to set the default cmake options.
Artifacts are stored in the build directory, under build/Debug/src or build/Release/src.

## Getting Started

```BASH
cmake --preset=debug # choose one of the presets in CMakePresets.json
cmake --build --preset=debug # build the project with the debug preset, one of build presets in CMakePresets.json
```

## CTest

[CMakePresets.json](CMakePresets.json) defines various test configurations.

```BASH
ctest --preset=debug # run all tests with the debug preset
```
