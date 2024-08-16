# Getting Started

Make a buld directory and run cmake to generate the build files.

```BASH
mkdir build
cd build
cmake ..
```

# C++ Preprocessor

- [C++ Preprocessor](#c-preprocessor)
  - [Introduction](#introduction)
  - [Preprocessor Directives](#preprocessor-directives)
  - [Macros](#macros)
  - [Conditional Compilation](#conditional-compilation)
  - [File Inclusion](#file-inclusion)
  - [Practical Example](#practical-example)
  - [References](#references)

## Introduction

The C++ preprocessor is a program that processes the source code before it passes through the compiler. It is a text substitution tool that instructs the compiler to do required pre-processing before the actual compilation. The preprocessor directives are lines included in the code of our programs that are not program statements but directives for the preprocessor. These lines are always preceded by a hash sign (#).

```BASH
gcc -E file.cpp -o file.i # Preprocess the file and save the output to file.i
```

## Preprocessor Directives

The preprocessor directives are lines included in the code of our programs that are not program statements but directives for the preprocessor. These lines are always preceded by a hash sign (#). The preprocessor directives are used for various purposes such as defining constants, creating macros, conditional compilation, etc.

## Macros

A macro is a fragment of code which has been given a name. Whenever the name is used, it is replaced by the contents of the macro. There are two types of macros: object-like macros and function-like macros.

### Object-like Macros

### Function-like Macros

## Conditional Compilation

Conditional compilation allows us to include or exclude parts of the program according to the condition. The preprocessor directives #if, #else, #elif, #endif, #ifdef, and #ifndef are used for conditional compilation.

## File Inclusion

## Practical Example

```C++

## References
- [The Preprocessor: Everything You Need to Know](https://www.youtube.com/watch?v=6KNdGnUiRBM)
```
