# Config Library

A lightweight configuration file parser library written in C++ (C++17).

## Project Description

This library provides utilities to parse and manage configuration files with support for key-value pairs. It includes exception handling for common configuration errors.

## Features

- Parse configuration files
- Retrieve values as different types (bool, int, string)
- Custom exception handling for configuration errors
- Debug output support

## Building the project

```
> cd config_lib/build

> cmake ..
> make

// Run test
> ctest ----output-on-failure

// Clean the project
> make clean      # Remove built objects
> make clean-all  # Remove entire build directory
```

## Usage

```cpp
config::Config cfg;
cfg.load("path/to/config.file");

std::string value = cfg.get_string("key");
int intVal = cfg.get_int("key");
bool boolVal = cfg.get_bool("key");
```
