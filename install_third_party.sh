#!/bin/bash
# Bash script to download, build, and install third-party dependencies

set -e  # Exit on error

BUILD_TYPE="${1:-Release}"
BUILD_SHARED_LIBS="${2:-OFF}"

# Validate build type
if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" ]]; then
    echo "Error: Build type must be 'Debug' or 'Release'"
    echo "Usage: $0 [Debug|Release] [ON|OFF]"
    exit 1
fi

# Validate shared libs option
if [[ "$BUILD_SHARED_LIBS" != "ON" && "$BUILD_SHARED_LIBS" != "OFF" ]]; then
    echo "Error: BuildSharedLibs must be 'ON' or 'OFF'"
    echo "Usage: $0 [Debug|Release] [ON|OFF]"
    exit 1
fi

echo "Building third-party dependencies in $BUILD_TYPE mode (shared libs: $BUILD_SHARED_LIBS)..."

function download_and_unpack {
    local target_dir="$1"
    local zip_name="$2"
    local url="$3"
    local extracted_dir="$4"

    if [ ! -d "$target_dir" ]; then
        echo "Downloading $target_dir ..."
        local max_attempts=2
        local attempt=1

        while [ $attempt -le $max_attempts ]; do
            if [ $attempt -gt 1 ]; then
                echo "Retrying download (attempt $attempt)..."
                sleep 3
            fi

            # Try to download
            if wget -O "$zip_name" "$url" || curl -L -o "$zip_name" "$url"; then
                # Try to extract
                if unzip -q "$zip_name" -d "3rd_party"; then
                    # Try to move
                    if mv "$extracted_dir" "$target_dir"; then
                        rm "$zip_name"
                        return 0  # Success
                    else
                        echo "Error: Failed to move $extracted_dir to $target_dir (attempt $attempt)"
                    fi
                else
                    echo "Error: Failed to extract $zip_name (attempt $attempt)"
                fi
            else
                echo "Error: Failed to download $zip_name from $url (attempt $attempt)"
            fi

            # Clean up partial files before retrying
            rm -f "$zip_name"
            rm -rf "$extracted_dir"

            if [ $attempt -eq $max_attempts ]; then
                echo "Error: Failed to download and unpack after $max_attempts attempts"
                exit 1
            fi

            attempt=$((attempt + 1))
        done
    fi
}

# Download, build and install plog
download_and_unpack "3rd_party/plog" "plog-1.1.11.zip" "https://github.com/SergiusTheBest/plog/archive/refs/tags/1.1.11.zip" "3rd_party/plog-1.1.11"
cmake -S 3rd_party/plog -B 3rd_party/plog/build -DPLOG_BUILD_SAMPLES=OFF -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --install 3rd_party/plog/build --prefix "$PWD/install"

# Download, build and install nlohmann_json
download_and_unpack "3rd_party/nlohmann_json" "nlohmann_json-3.11.3.zip" "https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip" "3rd_party/json-3.11.3"
cmake -S 3rd_party/nlohmann_json -B 3rd_party/nlohmann_json/build -DJSON_BuildTests=OFF -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --install 3rd_party/nlohmann_json/build --prefix "$PWD/install"

# Download, build and install cpp-httplib
download_and_unpack "3rd_party/cpp-httplib" "cpp-httplib-v0.47.0.zip" "https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.47.0.zip" "3rd_party/cpp-httplib-0.47.0"
cmake -S 3rd_party/cpp-httplib -B 3rd_party/cpp-httplib/build -DHTTPLIB_USE_ZSTD_IF_AVAILABLE=OFF -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --install 3rd_party/cpp-httplib/build --prefix "$PWD/install"

# Download, build and install Google Test
download_and_unpack "3rd_party/googletest" "googletest-1.17.0.zip" "https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip" "3rd_party/googletest-1.17.0"
cmake -S 3rd_party/googletest -B 3rd_party/googletest/build -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --build 3rd_party/googletest/build --config "$BUILD_TYPE" -j
cmake --install 3rd_party/googletest/build --config "$BUILD_TYPE" --prefix "$PWD/install"

# Download, build and install Google Benchmark
download_and_unpack "3rd_party/benchmark" "benchmark-1.9.4.zip" "https://github.com/google/benchmark/archive/refs/tags/v1.9.4.zip" "3rd_party/benchmark-1.9.4"
cmake -S 3rd_party/benchmark -B 3rd_party/benchmark/build -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --build 3rd_party/benchmark/build --config "$BUILD_TYPE" -j
cmake --install 3rd_party/benchmark/build --config "$BUILD_TYPE" --prefix "$PWD/install"

# Download, build and install zlib
# zlib has its own ZLIB_BUILD_SHARED/ZLIB_BUILD_STATIC options and ignores BUILD_SHARED_LIBS, so it
# installs both flavours by default and FindZLIB may then pick the one we did not ask for.
download_and_unpack "3rd_party/zlib" "zlib-1.3.2.zip" "https://github.com/madler/zlib/archive/refs/tags/v1.3.2.zip" "3rd_party/zlib-1.3.2"
if [ "$BUILD_SHARED_LIBS" = "ON" ]; then
    ZLIB_BUILD_SHARED=ON
    ZLIB_BUILD_STATIC=OFF
else
    ZLIB_BUILD_SHARED=OFF
    ZLIB_BUILD_STATIC=ON
fi
cmake -S 3rd_party/zlib -B 3rd_party/zlib/build -DCMAKE_INSTALL_PREFIX="$PWD/install" -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS" -DZLIB_BUILD_SHARED="$ZLIB_BUILD_SHARED" -DZLIB_BUILD_STATIC="$ZLIB_BUILD_STATIC"
cmake --build 3rd_party/zlib/build --config "$BUILD_TYPE" -j
cmake --install 3rd_party/zlib/build --config "$BUILD_TYPE"

# Download, build and install CLI11
download_and_unpack "3rd_party/CLI11" "v2.7.2.zip" "https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.7.2.zip" "3rd_party/CLI11-2.7.2"
cmake -S 3rd_party/CLI11 -B 3rd_party/CLI11/build -DCLI11_BUILD_EXAMPLES=OFF -DCLI11_BUILD_TESTS=OFF -DCLI11_BUILD_DOCS=OFF -DBUILD_SHARED_LIBS="$BUILD_SHARED_LIBS"
cmake --install 3rd_party/CLI11/build --prefix "$PWD/install"

echo "Third-party dependencies installed successfully!"
