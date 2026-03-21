# JSON Parser in C++

A basic command-line JSON parser written in C++ (C++17). This parser reads JSON files, validates their structure, and provides a parsed representation of the JSON data.

## Project Description

This project implements a lightweight JSON parser that can:
- Parse and validate JSON files
- Support various JSON data types (objects, arrays, strings, numbers, booleans, null)
- Display parsed JSON structures
- Provide error reporting for invalid JSON

## Project Structure

```
json_parser/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── elements.h          # JSON element type definitions
│   ├── json.h              # JSON parser class definition
│   └── utils.h             # Utility functions
├── src/                    # Source files
│   ├── main.cpp            # Entry point
│   ├── json.cpp            # JSON parser implementation
│   └── elements.cpp        # Element type implementations
├── tests/                  # Test files
│   ├── step1/              # Basic step tests
│   ├── step2/              # Intermediate tests
│   ├── step3/              # Advanced tests
│   ├── step4/              # Complex tests
│   └── random/             # Random test cases
└── build/                  # Build output directory (generated)
```

## Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- Standard C++ library

## Compilation

### Basic Build
```bash
cd json_parser
cd build
cmake ..
make
```

### Clean Build
```bash
cd build
cmake ..
make clean-all
make
```

## Running the Parser

The parser takes a JSON file path as a command-line argument:

```bash
./jsoncpp <path-to-json-file>
```

### Example
```bash
./jsoncpp ../tests/step1/valid.json
```

**Expected output for valid JSON:**
```
Valid JSON Object 
JSON Object parsed : 
[parsed JSON structure]
```

**Expected output for invalid JSON:**
```
Unable to Parse json
```

## Supported JSON Types

The parser supports the following JSON data types:
- **Objects** - `{...}` *nested objects are not supported now*
- **Strings** - `"..."`
- **Numbers** - integers and floating-point numbers
- **Booleans** - `true`, `false`
- **Null** - `null`

## Data Structures

### Main Classes

- **`JSON`** - Main parser class that reads and parses JSON data
- **`JSONObject`** - Represents a JSON object with key-value pairs
- **`JSONString`** - Represents a JSON string value
- **`JSONNumber`** - Represents a JSON number value
- **`JSONBool`** - Represents a JSON boolean value
- **`JSONNull`** - Represents a JSON null value

All element types inherit from the base `Elements` class.

## Known Limitations & Pending Items

- [ ] Escape character handling in strings (quoted strings)
- [ ] Unicode support in string parsing
- [ ] Nested array parsing refinement
- [ ] Error messages with line/column information
- [ ] Pretty-printing with indentation levels
- [ ] Command-line options for output formatting
- [ ] Unit test framework integration
- [ ] Performance optimization for large files

## Notes

- The parser uses `std::unique_ptr` for memory management
- Strict compiler flags ensure code quality
- Error handling is basic; consider enhancing with detailed error reporting
