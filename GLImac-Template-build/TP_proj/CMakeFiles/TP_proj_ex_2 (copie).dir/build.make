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
include TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/depend.make

# Include the progress variables for this target.
include TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/progress.make

# Include the compile flags for this target's objects.
include TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/flags.make

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o: TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/flags.make
TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o: /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP_proj/ex_2\ (copie).cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_proj/CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.o"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o "CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.o" -c "/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP_proj/ex_2 (copie).cpp"

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.i"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP_proj/ex_2 (copie).cpp" > "CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.i"

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.s"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP_proj/ex_2 (copie).cpp" -o "CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.s"

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.requires:

.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.requires

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.provides: TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.requires
	$(MAKE) -f "TP_proj/CMakeFiles/TP_proj_ex_2 (copie).dir/build.make" "TP_proj/CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.o.provides.build"
.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.provides

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.provides.build: TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o


# Object files for target TP_proj_ex_2 (copie)
TP_proj_ex_2 (copie)_OBJECTS = \
"CMakeFiles/TP_proj_ex_2 (copie).dir/ex_2_(copie).cpp.o"

# External object files for target TP_proj_ex_2 (copie)
TP_proj_ex_2 (copie)_EXTERNAL_OBJECTS =

TP_proj/TP_proj_ex_2\ (copie): TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o
TP_proj/TP_proj_ex_2\ (copie): TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/build.make
TP_proj/TP_proj_ex_2\ (copie): assimp/code/libassimp.so.4.0.1
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/libSDL.so
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/libGL.so.1
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/libGLEW.so
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/libz.so
TP_proj/TP_proj_ex_2\ (copie): assimp/contrib/irrXML/libIrrXML.a
TP_proj/TP_proj_ex_2\ (copie): /usr/lib/x86_64-linux-gnu/librt.so
TP_proj/TP_proj_ex_2\ (copie): TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable \"TP_proj_ex_2 (copie)\""
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj && $(CMAKE_COMMAND) -E cmake_link_script "CMakeFiles/TP_proj_ex_2 (copie).dir/link.txt" --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/build: TP_proj/TP_proj_ex_2\ (copie)

.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/build

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/requires: TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/ex_2_(copie).cpp.o.requires

.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/requires

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj && $(CMAKE_COMMAND) -P "CMakeFiles/TP_proj_ex_2 (copie).dir/cmake_clean.cmake"
.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/clean

TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/TP_proj /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj "/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/TP_proj/CMakeFiles/TP_proj_ex_2 (copie).dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : TP_proj/CMakeFiles/TP_proj_ex_2\ (copie).dir/depend

