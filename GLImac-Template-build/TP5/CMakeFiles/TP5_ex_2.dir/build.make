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
include TP5/CMakeFiles/TP5_ex_2.dir/depend.make

# Include the progress variables for this target.
include TP5/CMakeFiles/TP5_ex_2.dir/progress.make

# Include the compile flags for this target's objects.
include TP5/CMakeFiles/TP5_ex_2.dir/flags.make

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o: TP5/CMakeFiles/TP5_ex_2.dir/flags.make
TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o: /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP5/ex_2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o -c /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP5/ex_2.cpp

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP5_ex_2.dir/ex_2.cpp.i"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP5/ex_2.cpp > CMakeFiles/TP5_ex_2.dir/ex_2.cpp.i

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP5_ex_2.dir/ex_2.cpp.s"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP5/ex_2.cpp -o CMakeFiles/TP5_ex_2.dir/ex_2.cpp.s

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.requires:

.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.requires

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.provides: TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.requires
	$(MAKE) -f TP5/CMakeFiles/TP5_ex_2.dir/build.make TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.provides.build
.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.provides

TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.provides.build: TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o


# Object files for target TP5_ex_2
TP5_ex_2_OBJECTS = \
"CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o"

# External object files for target TP5_ex_2
TP5_ex_2_EXTERNAL_OBJECTS =

TP5/TP5_ex_2: TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o
TP5/TP5_ex_2: TP5/CMakeFiles/TP5_ex_2.dir/build.make
TP5/TP5_ex_2: glimac/libglimac.so
TP5/TP5_ex_2: assimp/code/libassimp.so.4.0.1
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/libSDL.so
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/libz.so
TP5/TP5_ex_2: assimp/contrib/irrXML/libIrrXML.a
TP5/TP5_ex_2: /usr/lib/x86_64-linux-gnu/librt.so
TP5/TP5_ex_2: TP5/CMakeFiles/TP5_ex_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP5_ex_2"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP5_ex_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP5/CMakeFiles/TP5_ex_2.dir/build: TP5/TP5_ex_2

.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/build

TP5/CMakeFiles/TP5_ex_2.dir/requires: TP5/CMakeFiles/TP5_ex_2.dir/ex_2.cpp.o.requires

.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/requires

TP5/CMakeFiles/TP5_ex_2.dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 && $(CMAKE_COMMAND) -P CMakeFiles/TP5_ex_2.dir/cmake_clean.cmake
.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/clean

TP5/CMakeFiles/TP5_ex_2.dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP5 /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5 /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP5/CMakeFiles/TP5_ex_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP5/CMakeFiles/TP5_ex_2.dir/depend

