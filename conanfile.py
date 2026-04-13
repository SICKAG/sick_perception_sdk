from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.files import load

required_conan_version = ">=2.13"


class SickPerceptionSDK(ConanFile):
    name = "sick_perception_sdk"
    description = "This packages contains SDK components for interacting with SICK sensors."
    license = "Copyright SICK AG"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "Version.txt", "CMakeLists.txt", "cmake/*", "src/*", "LICENSE", "README.md"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "build_drivers": [True, False],
        "build_benchmarks": [True, False],
        "build_compact_format": [True, False],
        "build_examples": [True, False],
        "build_drivers": [True, False],
        "build_sensor_configuration": [True, False],
        "build_unit_tests": [True, False],
        "build_examples_device_type": [None, "all", "picoScan100", "multiScan100", "LRS4000"],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "build_drivers": True,
        "build_benchmarks": False,
        "build_compact_format": True,
        "build_drivers": True,
        "build_examples": False,
        "build_sensor_configuration": True,
        "build_unit_tests": False,
        "build_examples_device_type": None,
    }

    def set_version(self):
        version_file = load(self, "Version.txt")
        # Extract version from: version="1.0.1"
        for line in version_file.split("\n"):
            if line.startswith("version="):
                self.version = line.split('"')[1]
                break

    def configure(self):
        if self.options.get_safe("shared"):
            del self.options.fPIC

        # Configure OpenSSL linking strategy:
        # - Dynamic runtime (/MD) requires shared OpenSSL to avoid runtime library conflicts
        # - Shared SDK build uses shared OpenSSL
        # - Static SDK build with static runtime (/MT) uses static OpenSSL
        if self.settings.compiler == "msvc" and self.settings.compiler.runtime == "dynamic":
            self.options["openssl"].shared = True
        elif self.options.get_safe("shared"):
            self.options["openssl"].shared = True
        else:
            self.options["openssl"].shared = False

        # Match gtest runtime to compiler settings when building unit tests
        if self.options.build_unit_tests:
            if self.settings.compiler == "msvc" and self.settings.compiler.runtime == "dynamic":
                self.options["gtest"].shared = True
            else:
                self.options["gtest"].shared = False

        # Match gtest runtime to compiler settings when building benchmarks
        if self.options.build_benchmarks:
            if self.settings.compiler == "msvc" and self.settings.compiler.runtime == "dynamic":
                self.options["benchmark"].shared = True
            else:
                self.options["benchmark"].shared = False

    def requirements(self):
        self.requires("plog/[^1.1.10]")
        if self.options.get_safe("build_sensor_configuration") or self.options.get_safe("build_drivers") or self.options.get_safe("build_examples_device_type") != None:
            self.requires("cpp-httplib/[^0.39.0]", transitive_headers=True)
            self.requires("nlohmann_json/[^3.11.0]", transitive_headers=True)
            self.requires("openssl/[^3.6]", transitive_headers=True)
        if self.options.get_safe("build_compact_format") or self.options.get_safe("build_drivers") or self.options.get_safe("build_examples_device_type") != None:
            # Caution: zlib 1.3.2 introduces cmake changes that are not compatible to sick_perception_sdk's CMakeLists.txt.
            self.requires("zlib/1.3.1")
        if self.options.get_safe("build_unit_tests"):
            self.test_requires("gtest/[^1.16.0]")
        if self.options.build_benchmarks:
            self.test_requires("benchmark/1.9.4")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.variables["BUILD_DRIVERS"] = self.options.build_drivers
        tc.variables["BUILD_BENCHMARKS"] = self.options.build_benchmarks
        tc.variables["BUILD_COMPACT_FORMAT"] = self.options.build_compact_format
        tc.variables["BUILD_DRIVERS"] = self.options.build_drivers
        tc.variables["BUILD_EXAMPLES"] = self.options.build_examples
        tc.variables["BUILD_SENSOR_CONFIGURATION"] = self.options.build_sensor_configuration
        tc.variables["BUILD_UNIT_TESTS"] = self.options.build_unit_tests
        tc.variables["BUILD_EXAMPLES_DEVICE_TYPE"] = "" if self.options.build_examples_device_type == None else str(self.options.build_examples_device_type)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(
            variables={
                "BUILD_SHARED_LIBS": self.options.shared,
                "BUILD_DRIVERS": self.options.build_drivers,
                "BUILD_BENCHMARKS": self.options.build_benchmarks,
                "BUILD_COMPACT_FORMAT": self.options.build_compact_format,
                "BUILD_DRIVERS": self.options.build_drivers,
                "BUILD_EXAMPLES": self.options.build_examples,
                "BUILD_SENSOR_CONFIGURATION": self.options.build_sensor_configuration,
                "BUILD_UNIT_TESTS": self.options.build_unit_tests,
                "BUILD_EXAMPLES_DEVICE_TYPE": "" if self.options.build_examples_device_type == None else str(self.options.build_examples_device_type),
            }
        )
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        # Set the CMake config file location
        self.cpp_info.set_property("cmake_file_name", "sick_perception_sdk")

        # Define the common component (always required)
        self.cpp_info.components["common"].libs = ["common"]
        self.cpp_info.components["common"].set_property("cmake_target_name", "sick_perception_sdk::common")
        self.cpp_info.components["common"].requires = ["plog::plog"]

        # Define library components based on what was built
        if self.options.get_safe("build_drivers"):
            self.cpp_info.components["drivers"].libs = ["drivers"]
            self.cpp_info.components["drivers"].set_property("cmake_target_name", "sick_perception_sdk::drivers")
            self.cpp_info.components["drivers"].requires = ["common", "compact_format", "sensor_configuration", "cpp-httplib::cpp-httplib", "nlohmann_json::nlohmann_json", "openssl::openssl"]
            self.cpp_info.components["drivers"].requires.append("zlib::zlib")

        if self.options.get_safe("build_compact_format"):
            self.cpp_info.components["compact_format"].libs = ["compact_format"]
            self.cpp_info.components["compact_format"].set_property("cmake_target_name", "sick_perception_sdk::compact_format")
            self.cpp_info.components["compact_format"].requires = ["common", "zlib::zlib"]

        if self.options.get_safe("build_sensor_configuration"):
            self.cpp_info.components["sensor_configuration"].libs = ["sensor_configuration"]
            self.cpp_info.components["sensor_configuration"].set_property("cmake_target_name", "sick_perception_sdk::sensor_configuration")
            self.cpp_info.components["sensor_configuration"].requires = ["common", "cpp-httplib::cpp-httplib", "nlohmann_json::nlohmann_json", "openssl::openssl"]
