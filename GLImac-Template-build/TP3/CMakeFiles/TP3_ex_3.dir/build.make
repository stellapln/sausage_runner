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

# Include any dependencies generated for this target.
include TP3/CMakeFiles/TP3_ex_3.dir/depend.make

# Include the progress variables for this target.
include TP3/CMakeFiles/TP3_ex_3.dir/progress.make

# Include the compile flags for this target's objects.
include TP3/CMakeFiles/TP3_ex_3.dir/flags.make

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o: TP3/CMakeFiles/TP3_ex_3.dir/flags.make
TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o: /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP3/ex_3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o -c /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP3/ex_3.cpp

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP3_ex_3.dir/ex_3.cpp.i"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP3/ex_3.cpp > CMakeFiles/TP3_ex_3.dir/ex_3.cpp.i

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP3_ex_3.dir/ex_3.cpp.s"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP3/ex_3.cpp -o CMakeFiles/TP3_ex_3.dir/ex_3.cpp.s

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.requires:

.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.requires

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.provides: TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.requires
	$(MAKE) -f TP3/CMakeFiles/TP3_ex_3.dir/build.make TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.provides.build
.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.provides

TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.provides.build: TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o


# Object files for target TP3_ex_3
TP3_ex_3_OBJECTS = \
"CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o"

# External object files for target TP3_ex_3
TP3_ex_3_EXTERNAL_OBJECTS =

TP3/TP3_ex_3: TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o
TP3/TP3_ex_3: TP3/CMakeFiles/TP3_ex_3.dir/build.make
TP3/TP3_ex_3: glimac/libglimac.so
TP3/TP3_ex_3: assimp/code/libassimp.so.4.0.1
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/libSDL.so
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/libz.so
TP3/TP3_ex_3: assimp/contrib/irrXML/libIrrXML.a
TP3/TP3_ex_3: /usr/lib/x86_64-linux-gnu/librt.so
TP3/TP3_ex_3: TP3/CMakeFiles/TP3_ex_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP3_ex_3"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP3_ex_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP3/CMakeFiles/TP3_ex_3.dir/build: TP3/TP3_ex_3

.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/build

TP3/CMakeFiles/TP3_ex_3.dir/requires: TP3/CMakeFiles/TP3_ex_3.dir/ex_3.cpp.o.requires

.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/requires

TP3/CMakeFiles/TP3_ex_3.dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 && $(CMAKE_COMMAND) -P CMakeFiles/TP3_ex_3.dir/cmake_clean.cmake
.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/clean

TP3/CMakeFiles/TP3_ex_3.dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP3 /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3 /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP3/CMakeFiles/TP3_ex_3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP3/CMakeFiles/TP3_ex_3.dir/depend

