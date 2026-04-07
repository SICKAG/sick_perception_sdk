# Developing and Contributing

## Code Style Guidelines

Here are some friendly guidelines to follow when contributing code to this project. They are neither complete nor strict rules, but following them helps to keep the codebase consistent and maintainable.

- Write code that does not need documentation. Use self-explanatory names and decompose complex functions into smaller functions with descriptive names.
- Avoid superfluous documentation:
  - Classes and functions do not need documentation if their name clearly describes their purpose.
  - Do not repeat the code in documentation.
  - If necessary, document **underlying concepts** of a class or function, not **what** the code is doing in detail.
  - It may be beneficial to use line comments inside long functions to structure the code into blocks. The comment should describe the block's purpose, not repeat the code.
- If necessary, document classes and functions using doxygen style comments surrounded by block comments `/** ... */` and reference doxygen keywords by `@`.
- Use `camelCase` for variable and function names. Use `PascalCase` for class and struct names. Constants should be named using `kConstantName`.
- Use `constexpr` for constant values instead of `#define`.
- Use `override` for all overridden virtual functions.
- Write test case names in `snake_case`. The name should resemble a sentence that describes the tested condition and the expected outcome; test cases should not need additional documentation.
- `#include`s are ordered into three blocks with a blank line between each block:
  - First block (in a cpp file): the header of the corresponding class. Obviously, this does not apply to header files.
  - Second block: headers from the SDK.
  - Third block: standard library and third party headers.
  - Each block of headers is sorted alphabetically. Sorting the headers is done automatically by clang-format.
- Auto-format the code using clang format (see below); don't get hung up on formatting details or manual formatting.
- Put a comma behind all elements of an enum, even the last one. This makes adding or moving new elements easier and results in cleaner diffs.
- Sort things alphabetically where it makes sense (e.g. CMakeLists, some enums).

## Code Formatting

All C++ code except generated code is formatted automatically using [clang format](https://clang.llvm.org/docs/ClangFormat.html). The configuration file `.clang-format` is in the root directory.

A convenient way to install clang format is using pip, either system-wide or into a virtual environment.

To format all files at once execute in bash

```sh
find src -type f -name "*.*pp" ! -name "*.g.hpp" | xargs clang-format -i -Werror --style=file:.clang-format
```

or PowerShell

```powershell
Get-ChildItem -Recurse -Path src -Include *.cpp,*.hpp,*.cxx,*.hxx | Where-Object { $_.Name -notlike "*.g.hpp" } | ForEach-Object { clang-format -i -Werror --style=file:.clang-format $_.FullName }
```

from the project root directory.

## Code Generation from OpenAPI

> [!NOTE]
>
> Executing the code generator is only necessary when adding support for new devices or updating the generated code after changes to the OpenAPI descriptions.

- Code generation is done by the script `/openapi_generator/parse_open_api.py`.
- The OpenAPI descriptions for the supported devices are stored in `/openapi_generator/schema`.
- The generator can be invoked for all devices by executing the script `/generate_openapi.sh` from the project root directory.
- The generator's requirements are listed in `/requirements.txt`
