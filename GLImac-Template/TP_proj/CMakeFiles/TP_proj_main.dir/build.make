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
CMAKE_SOURCE_DIR = /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template

# Include any dependencies generated for this target.
include TP_proj/CMakeFiles/TP_proj_main.dir/depend.make

# Include the progress variables for this target.
include TP_proj/CMakeFiles/TP_proj_main.dir/progress.make

# Include the compile flags for this target's objects.
include TP_proj/CMakeFiles/TP_proj_main.dir/flags.make

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o: TP_proj/CMakeFiles/TP_proj_main.dir/flags.make
TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o: TP_proj/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o"
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP_proj_main.dir/main.cpp.o -c /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj/main.cpp

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP_proj_main.dir/main.cpp.i"
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj/main.cpp > CMakeFiles/TP_proj_main.dir/main.cpp.i

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP_proj_main.dir/main.cpp.s"
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj/main.cpp -o CMakeFiles/TP_proj_main.dir/main.cpp.s

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.requires:

.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.requires

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.provides: TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.requires
	$(MAKE) -f TP_proj/CMakeFiles/TP_proj_main.dir/build.make TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.provides.build
.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.provides

TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.provides.build: TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o


# Object files for target TP_proj_main
TP_proj_main_OBJECTS = \
"CMakeFiles/TP_proj_main.dir/main.cpp.o"

# External object files for target TP_proj_main
TP_proj_main_EXTERNAL_OBJECTS =

TP_proj/TP_proj_main: TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o
TP_proj/TP_proj_main: TP_proj/CMakeFiles/TP_proj_main.dir/build.make
TP_proj/TP_proj_main: glimac/libglimac.so
TP_proj/TP_proj_main: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP_proj/TP_proj_main: /usr/lib/x86_64-linux-gnu/libSDL.so
TP_proj/TP_proj_main: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP_proj/TP_proj_main: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP_proj/TP_proj_main: TP_proj/CMakeFiles/TP_proj_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP_proj_main"
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP_proj_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_proj/CMakeFiles/TP_proj_main.dir/build: TP_proj/TP_proj_main

.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/build

TP_proj/CMakeFiles/TP_proj_main.dir/requires: TP_proj/CMakeFiles/TP_proj_main.dir/main.cpp.o.requires

.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/requires

TP_proj/CMakeFiles/TP_proj_main.dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj && $(CMAKE_COMMAND) -P CMakeFiles/TP_proj_main.dir/cmake_clean.cmake
.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/clean

TP_proj/CMakeFiles/TP_proj_main.dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj /home/6im2/bmantova/Documents/CPP-S3/sausage_runner/GLImac-Template/TP_proj/CMakeFiles/TP_proj_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP_proj/CMakeFiles/TP_proj_main.dir/depend
