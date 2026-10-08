# Developing and Contributing

## Source Of Truth And Sync Policy

To keep contributor and agent guidance in sync:

- [AGENTS.md](AGENTS.md) is the canonical source for build, test, validation, source layout, and code generation workflow commands.
- [.agents/instructions/cpp.instructions.md](.agents/instructions/cpp.instructions.md) is the canonical source for detailed C++ style and language constraints.
- This file should stay concise and avoid duplicating operational command blocks from AGENTS. Prefer links to canonical sections.

When changing workflow rules, update the canonical source first, then adjust links and summaries here in the same PR.

## Code Style Guidelines

Follow the canonical C++ style and language rules in [.agents/instructions/cpp.instructions.md](.agents/instructions/cpp.instructions.md). That file contains the non-formatting conventions that are not enforced by clang-format.

In short:

- Keep code self-explanatory and avoid redundant documentation.
- Prefer consistency with existing naming, includes, and test naming conventions.
- Use clang-format for formatting and treat non-formatting rules from the cpp instructions as authoritative.

## Code Formatting

All C++ code except generated code is formatted automatically using [clang format](https://clang.llvm.org/docs/ClangFormat.html). The configuration file `.clang-format` is in the repository root.

For canonical formatting commands, see the **Code Style** section in [AGENTS.md](AGENTS.md).

## Code Generation from OpenAPI

> [!NOTE]
>
> Executing the code generator is only necessary when adding support for new devices or updating the generated code after changes to the OpenAPI descriptions.

- Code generation is done by the script `/openapi_generator/parse_open_api.py`.
- The OpenAPI descriptions for the supported devices are stored in `/openapi_generator/schema`.
- The generator can be invoked for all devices by executing the script `/generate_openapi.sh` from the project root directory.
- The generator's requirements are listed in `/requirements.txt`

For canonical code generation workflow details (including generated header locations), see [AGENTS.md](AGENTS.md).
