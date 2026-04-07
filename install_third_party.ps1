# PowerShell script to download, build, and install third-party dependencies for Windows

param(
	[Parameter(Mandatory=$false)]
	[ValidateSet("Debug", "Release")]
	[string]$BuildType = "Release"
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
cmake -S 3rd_party/plog -B 3rd_party/plog/build -DPLOG_BUILD_SAMPLES=OFF
cmake --install 3rd_party/plog/build --prefix "$PWD/install"

# Download, build and install nlohmann_json
Download-And-Unpack -TargetDir "3rd_party/nlohmann_json" -ZipName "nlohmann_json-3.12.0.zip" -Url "https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip" -ExtractedDir "3rd_party/json-3.12.0"
cmake -S 3rd_party/nlohmann_json -B 3rd_party/nlohmann_json/build -DJSON_BuildTests=OFF
cmake --install 3rd_party/nlohmann_json/build --prefix "$PWD/install"

# Download, build and install cpp-httplib
Download-And-Unpack -TargetDir "3rd_party/cpp-httplib" -ZipName "cpp-httplib-v0.39.0.zip" -Url "https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.39.0.zip" -ExtractedDir "3rd_party/cpp-httplib-0.39.0"
cmake -S 3rd_party/cpp-httplib -B 3rd_party/cpp-httplib/build
cmake --install 3rd_party/cpp-httplib/build --prefix "$PWD/install"

# Download, build and install Google Test
Download-And-Unpack -TargetDir "3rd_party/googletest" -ZipName "googletest-1.17.0.zip" -Url "https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip" -ExtractedDir "3rd_party/googletest-1.17.0"
# Use static runtime (MT/MTd) to match OpenSSL from slproweb.com
$RuntimeLibrary = if ($BuildType -eq "Debug") { "MultiThreadedDebug" } else { "MultiThreaded" }
cmake -S 3rd_party/googletest -B 3rd_party/googletest/build -Dgtest_force_shared_crt=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$RuntimeLibrary"
cmake --build 3rd_party/googletest/build --config $BuildType
cmake --install 3rd_party/googletest/build --prefix "$PWD/install" --config $BuildType

# Download, build and install Google Benchmark
Download-And-Unpack -TargetDir "3rd_party/benchmark" -ZipName "benchmark-1.9.4.zip" -Url "https://github.com/google/benchmark/archive/refs/tags/v1.9.4.zip" -ExtractedDir "3rd_party/benchmark-1.9.4"
# Use static runtime (MT/MTd) to match OpenSSL from slproweb.com
$RuntimeLibrary = if ($BuildType -eq "Debug") { "MultiThreadedDebug" } else { "MultiThreaded" }
cmake -S 3rd_party/benchmark -B 3rd_party/benchmark/build -Dgtest_force_shared_crt=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="$RuntimeLibrary" -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
cmake --build 3rd_party/benchmark/build --config $BuildType
cmake --install 3rd_party/benchmark/build --prefix "$PWD/install" --config $BuildType

# Download, build and install zlib
Download-And-Unpack -TargetDir "3rd_party/zlib" -ZipName "zlib-1.3.1.zip" -Url "https://github.com/madler/zlib/archive/refs/tags/v1.3.1.zip" -ExtractedDir "3rd_party/zlib-1.3.1"
cmake -S 3rd_party/zlib -B 3rd_party/zlib/build -DCMAKE_INSTALL_PREFIX="$PWD/install" -DCMAKE_MSVC_RUNTIME_LIBRARY="$RuntimeLibrary"
cmake --build 3rd_party/zlib/build --config $BuildType
cmake --install 3rd_party/zlib/build --config $BuildType
