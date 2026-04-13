When asked to install the SDK you need to execute the following steps:

1. `cmake -S . -B build -DCMAKE_PREFIX_PATH="$PWD/install" -DCMAKE_INSTALL_PREFIX="$PWD/install_sdk" -DCMAKE_BUILD_TYPE=Release`
2. `cmake --build build --target install -j`

When asked to build the examples add `-DBUILD_EXAMPLES=ON` to the cmake configuration command.

A dynamic build can be created by adding `-DBUILD_SHARED_LIBS=ON` to the cmake configuration command.

When asked to build an example you need to execute the following steps:

1. `cd examples/picoScan100`
2. `cmake -S . -B build -DCMAKE_PREFIX_PATH="$PWD/../../install;$PWD/../../install_sdk" -DCMAKE_BUILD_TYPE=Release`
3. `cmake --build build -j --config Release`

On Windows, remove `$PWD/` to avoid issues with path formats.

For running cmake you need to activate .venv if this folder exists.

If not otherwise instructed you don't need to make sure that your changes are backwards compatible.
