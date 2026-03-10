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
