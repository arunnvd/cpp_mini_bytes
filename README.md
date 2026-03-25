# Simple Byte-sized C/C++ Projects

A collection of lightweight, educational C/C++ projects designed for learning and skill development. Each project focuses on core programming concepts while remaining simple enough to understand and extend.


## 🎯 Learning Objectives

Through these projects, you will:
- Master fundamental C++ syntax and semantics
- Understand object-oriented programming (OOP) principles
- Learn to structure code using classes and design patterns
- Practice CMake build system configuration
- Gain experience with proper code organization and header files
- Implement game logic and interactive programs
- Learn best practices for code quality and maintainability



## 🚀 Projects Included

### 1. Number Guessing Game
A simple interactive game where players guess a randomly generated number.
```
guessing_game/               # Number guessing game project
    ├── README.md                # Project-specific documentation
    ├── CMakeLists.txt           # CMake build configuration
    ├── include/                 # Header files
    │   ├── game.h               # Game logic interface
    │   └── magic_number.h       # Random number generation
    ├── src/                     # Source files
    │   ├── main.cpp             # Entry point
    │   └── game.cpp             # Game implementation
    └── build/                   # Build output directory
```


**Build & Run:**
```bash
cd guessing_game/build
cmake ..
make
./guessinggame
```

[Full Details](./guessing_game/README.md)

### 2. Config Library
A lightweight configuration file parser library written in C++ (17) that provides utilities to parse and manage configuration files with support for key-value pairs.

```
config_lib/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # Project-specific documentation
├── include/                # Header files
│   └── configlib.h         # Configuration library interface
├── src/                    # Source files
│   ├── configlib.cpp       # Config implementation
│   └── config_exception.cpp # Exception handling
└── build/                  # Build output directory (generated)
```

**Build & Run:**
```bash
cd config_lib/build
cmake ..
make
```

[Full Details](./config_lib/README.md)

### 3. JSON Parser
A lightweight JSON parser written in C++ (17) that can parse and validate JSON files, display parsed stryctures.   

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
**Build & Run**
```bash
cd json_parser
cd build
cmake ..
make

./jsoncpp <path-to-json-file>
```

[Full Details](./json_parser/README.md)

### 4. SSE Client Library
A lightweight Server-Sent Events (SSE) client library written in C++ (17) that provides utilities to connect to SSE endpoints and receive real-time events from servers.

```
sse_client/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # Project-specific documentation
├── include/                # Header files
│   └── sseclient.h         # SSE client library interface
├── src/                    # Source files
│   └── sseclient.cpp       # SSE client implementation
├── tests/                  # Test files
│   └── test_main.cpp       # Unit tests
└── build/                  # Build output directory (generated)
```

**Build & Run:**
```bash
cd sse_client/build
cmake ..
make
ctest --output-on-failure
```

[Full Details](./sse_client/README.md)

## 📋 Prerequisites

- **C++ Compiler** (GCC, Clang, or MSVC with C++17 support)
- **CMake** (version 3.16 or higher)
- **Make** or compatible build tool
- **Git** (for cloning the repository)


## 💻 Requirements & Standards

All projects in this repository:
- Use **C++17** or newer standard
- Employ **CMake** for build configuration
- Include **strict compiler flags** (-Wall, -Wextra, -Wpedantic, -Werror)
- Follow **OOP design principles**
- Maintain clean, readable code structure


**Note:** All projects are intentionally kept simple and focused on core concepts rather than advanced features or production-grade code.
