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
CMAKE_SOURCE_DIR = /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build

# Utility rule file for ExperimentalStart.

# Include the progress variables for this target.
include assimp/test/CMakeFiles/ExperimentalStart.dir/progress.make

assimp/test/CMakeFiles/ExperimentalStart:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/test && /usr/bin/ctest -D ExperimentalStart

ExperimentalStart: assimp/test/CMakeFiles/ExperimentalStart
ExperimentalStart: assimp/test/CMakeFiles/ExperimentalStart.dir/build.make

.PHONY : ExperimentalStart

# Rule to build all files generated by this target.
assimp/test/CMakeFiles/ExperimentalStart.dir/build: ExperimentalStart

.PHONY : assimp/test/CMakeFiles/ExperimentalStart.dir/build

assimp/test/CMakeFiles/ExperimentalStart.dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/test && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalStart.dir/cmake_clean.cmake
.PHONY : assimp/test/CMakeFiles/ExperimentalStart.dir/clean

assimp/test/CMakeFiles/ExperimentalStart.dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/test /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/test /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/test/CMakeFiles/ExperimentalStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : assimp/test/CMakeFiles/ExperimentalStart.dir/depend

