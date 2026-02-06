# AGENTS.md

This document provides guidelines for agentic coding agents operating in this repository.

## Build/Lint/Test Commands

- **Build**: `powershell.exe pio run` or `powershell.exe platformio run`
- **Upload/Deploy**: `powershell.exe pio run --target upload` or `powershell.exe platformio run --target upload`
- **Clean**: `powershell.exe pio run --target clean` or `powershell.exe platformio run --target clean`
- **Test**: PlatformIO doesn't have a standard test framework - tests are typically written and run manually or via custom scripts
- **Format**: Use `clang-format` for C++ files (following Arduino style guide)

## Code Style Guidelines

### Imports
- Use standard Arduino library includes with `#include <Arduino.h>`
- Use `#include "filename.h"` for project-specific headers
- Group standard library includes before project includes
- Sort includes alphabetically within groups

### Formatting
- Follow Arduino C++ coding style conventions
- Indentation: 2 spaces (not tabs)
- Line length: 120 characters maximum
- Use curly braces for all control flow statements
- Function parameters and return types should be on the same line
- Use `camelCase` for variables and functions

### Types
- Use standard C++ types (int, char, bool, etc.)
- Prefer `const` for values that don't change
- Use typedefs or using statements for complex types when needed
- Use explicit casting for type conversions

### Naming Conventions
- Variables and functions: camelCase
- Constants: UPPER_CASE
- Classes and structures: PascalCase
- Files: kebab-case for source files, .cpp/.h extension
- Prefix global variables with `g_` if needed

### Error Handling
- Use standard Arduino error handling patterns
- Return early from functions when errors occur
- Use `assert()` macro for debugging assertions
- Handle hardware-specific errors appropriately

### Documentation
- Document all public functions with Doxygen-style comments
- Add code comments for complex logic
- Use descriptive names for variables and functions
- Include brief descriptions in header files for all public APIs

## Special Rules

### Copilot Instructions
- Use standard Arduino and C++ conventions
- Follow the Arduino coding style guide
- Maintain compatibility with ATmega32U4 microcontroller (Leonardo board)
- Respect memory constraints of embedded systems

### Cursor Rules
- Follow the project's existing code style and patterns
- Maintain readability and code quality
- Prioritize clarity over cleverness
- Respect embedded system resource constraints (memory, processing power)