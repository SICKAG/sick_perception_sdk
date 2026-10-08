# PowerShell script to download, build, and install third-party dependencies for Windows

param(
	[Parameter(Mandatory=$false)]
	[ValidateSet("Debug", "Release")]
	[string]$BuildType = "Release",
	[Parameter(Mandatory=$false)]
	[ValidateSet("ON", "OFF")]
	[string]$BuildSharedLibs = "OFF",
	[Parameter(Mandatory=$false)]
	[ValidateSet("MultiThreaded", "MultiThreadedDLL", "MultiThreadedDebug", "MultiThreadedDebugDLL")]
	[string]$CmakeMSVCRuntimeLibrary = "MultiThreaded"
)

# Set error action preference to stop on any error
$ErrorActionPreference = "Stop"

Write-Host "Building third-party dependencies in $BuildType mode..."

function Download-And-Unpack {
	param(
		[string]$TargetDir,
		[string]$ZipName,
		[string]$Url,
		[string]$ExtractedDir
	)
	if (-not (Test-Path $TargetDir)) {
		Write-Host "Downloading $TargetDir ..."
		$maxAttempts = 2
		$attempt = 1

		while ($attempt -le $maxAttempts) {
			try {
				if ($attempt -gt 1) {
					Write-Host "Retrying download (attempt $attempt)..."
					Start-Sleep -Seconds 3
				}

				Invoke-WebRequest -Uri $Url -OutFile $ZipName
				Expand-Archive -Path $ZipName -DestinationPath "3rd_party" -Force
				Move-Item -Path $ExtractedDir -Destination $TargetDir
				Remove-Item $ZipName
				break  # Success, exit the retry loop
			}
			catch {
				if ($attempt -eq $maxAttempts) {
					Write-Error "Failed to download and unpack $TargetDir after $maxAttempts attempts: $_"
					throw
				}
				Write-Host "Attempt $attempt failed: $_"
				# Clean up any partial files before retrying
				if (Test-Path $ZipName) { Remove-Item $ZipName -Force }
				if (Test-Path $ExtractedDir) { Remove-Item $ExtractedDir -Recurse -Force }
				$attempt++
			}
		}
	}
}

# Download, build and install plog
Download-And-Unpack -TargetDir "3rd_party/plog" -ZipName "plog-1.1.11.zip" -Url "https://github.com/SergiusTheBest/plog/archive/refs/tags/1.1.11.zip" -ExtractedDir "3rd_party/plog-1.1.11"
cmake -S 3rd_party/plog -B 3rd_party/plog/build -DPLOG_BUILD_SAMPLES=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --install 3rd_party/plog/build --prefix "$PWD/install" --config $BuildType

# Download, build and install nlohmann_json
Download-And-Unpack -TargetDir "3rd_party/nlohmann_json" -ZipName "nlohmann_json-3.11.3.zip" -Url "https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip" -ExtractedDir "3rd_party/json-3.11.3"
cmake -S 3rd_party/nlohmann_json -B 3rd_party/nlohmann_json/build -DJSON_BuildTests=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --install 3rd_party/nlohmann_json/build --prefix "$PWD/install" --config $BuildType

# Download, build and install cpp-httplib
Download-And-Unpack -TargetDir "3rd_party/cpp-httplib" -ZipName "cpp-httplib-v0.47.0.zip" -Url "https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.47.0.zip" -ExtractedDir "3rd_party/cpp-httplib-0.47.0"
cmake -S 3rd_party/cpp-httplib -B 3rd_party/cpp-httplib/build -DHTTPLIB_USE_ZSTD_IF_AVAILABLE=OFF -DCMAKE_BUILD_TYPE="$BuildType" -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --install 3rd_party/cpp-httplib/build --prefix "$PWD/install" --config $BuildType

# Download, build and install Google Test
Download-And-Unpack -TargetDir "3rd_party/googletest" -ZipName "googletest-1.17.0.zip" -Url "https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip" -ExtractedDir "3rd_party/googletest-1.17.0"
# Use static runtime (MT/MTd) to match OpenSSL from slproweb.com
cmake -S 3rd_party/googletest -B 3rd_party/googletest/build -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --build 3rd_party/googletest/build --config $BuildType
cmake --install 3rd_party/googletest/build --prefix "$PWD/install" --config $BuildType

# Download, build and install Google Benchmark
Download-And-Unpack -TargetDir "3rd_party/benchmark" -ZipName "benchmark-1.9.4.zip" -Url "https://github.com/google/benchmark/archive/refs/tags/v1.9.4.zip" -ExtractedDir "3rd_party/benchmark-1.9.4"
# Use static runtime (MT/MTd) to match OpenSSL from slproweb.com
cmake -S 3rd_party/benchmark -B 3rd_party/benchmark/build -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --build 3rd_party/benchmark/build --config $BuildType
cmake --install 3rd_party/benchmark/build --prefix "$PWD/install" --config $BuildType

# Download, build and install zlib
# zlib has its own ZLIB_BUILD_SHARED/ZLIB_BUILD_STATIC options and ignores BUILD_SHARED_LIBS, so it
# installs both flavours by default. On Windows both are '.lib' and FindZLIB then picks the import
# library of z.dll, which a statically linked executable cannot load at runtime.
Download-And-Unpack -TargetDir "3rd_party/zlib" -ZipName "zlib-1.3.2.zip" -Url "https://github.com/madler/zlib/archive/refs/tags/v1.3.2.zip" -ExtractedDir "3rd_party/zlib-1.3.2"
if ($BuildSharedLibs -eq "ON") {
	$ZlibBuildShared = "ON"
	$ZlibBuildStatic = "OFF"
} else {
	$ZlibBuildShared = "OFF"
	$ZlibBuildStatic = "ON"
}
cmake -S 3rd_party/zlib -B 3rd_party/zlib/build -DCMAKE_INSTALL_PREFIX="$PWD/install" -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs" -DZLIB_BUILD_SHARED="$ZlibBuildShared" -DZLIB_BUILD_STATIC="$ZlibBuildStatic"
cmake --build 3rd_party/zlib/build --config $BuildType
cmake --install 3rd_party/zlib/build --config $BuildType
if ($ZlibBuildStatic -eq "ON") {
	# zlib suffixes its static library with 's' on Windows, a name FindZLIB only knows from CMake 4.0
	# on. Provide the plain name as well so older CMake finds the static library instead of failing.
	if ($BuildType -eq "Debug") {
		Copy-Item "install/lib/zsd.lib" "install/lib/zd.lib" -Force
	} else {
		Copy-Item "install/lib/zs.lib" "install/lib/z.lib" -Force
	}
}

# Download, build and install CLI11
Download-And-Unpack -TargetDir "3rd_party/CLI11" -ZipName "v2.7.2.zip" -Url "https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.7.2.zip" -ExtractedDir "3rd_party/CLI11-2.7.2"
cmake -S 3rd_party/CLI11 -B 3rd_party/CLI11/build -DCLI11_BUILD_EXAMPLES=OFF -DCLI11_BUILD_TESTS=OFF -DCLI11_BUILD_DOCS=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$CmakeMSVCRuntimeLibrary" -DBUILD_SHARED_LIBS="$BuildSharedLibs"
cmake --install 3rd_party/CLI11/build --prefix "$PWD/install" --config $BuildType

Write-Host "Third-party dependencies installed successfully!"
