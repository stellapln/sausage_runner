# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build

# Utility rule file for ExperimentalCoverage.

# Include the progress variables for this target.
include assimp/test/CMakeFiles/ExperimentalCoverage.dir/progress.make

assimp/test/CMakeFiles/ExperimentalCoverage:
	cd /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/test && /usr/bin/ctest -D ExperimentalCoverage

ExperimentalCoverage: assimp/test/CMakeFiles/ExperimentalCoverage
ExperimentalCoverage: assimp/test/CMakeFiles/ExperimentalCoverage.dir/build.make

.PHONY : ExperimentalCoverage

# Rule to build all files generated by this target.
assimp/test/CMakeFiles/ExperimentalCoverage.dir/build: ExperimentalCoverage

.PHONY : assimp/test/CMakeFiles/ExperimentalCoverage.dir/build

assimp/test/CMakeFiles/ExperimentalCoverage.dir/clean:
	cd /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/test && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalCoverage.dir/cmake_clean.cmake
.PHONY : assimp/test/CMakeFiles/ExperimentalCoverage.dir/clean

assimp/test/CMakeFiles/ExperimentalCoverage.dir/depend:
	cd /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template/assimp/test /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/test /home/6im2/spoula02/Documents/sausage_runner/GLImac-Template-build/assimp/test/CMakeFiles/ExperimentalCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : assimp/test/CMakeFiles/ExperimentalCoverage.dir/depend

