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
include assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/depend.make

# Include the progress variables for this target.
include assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/progress.make

# Include the compile flags for this target's objects.
include assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/flags.make

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/flags.make
assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o: /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/contrib/irrXML/irrXML.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IrrXML.dir/irrXML.cpp.o -c /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/contrib/irrXML/irrXML.cpp

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IrrXML.dir/irrXML.cpp.i"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/contrib/irrXML/irrXML.cpp > CMakeFiles/IrrXML.dir/irrXML.cpp.i

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IrrXML.dir/irrXML.cpp.s"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/contrib/irrXML/irrXML.cpp -o CMakeFiles/IrrXML.dir/irrXML.cpp.s

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.requires:

.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.requires

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.provides: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.requires
	$(MAKE) -f assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/build.make assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.provides.build
.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.provides

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.provides.build: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o


# Object files for target IrrXML
IrrXML_OBJECTS = \
"CMakeFiles/IrrXML.dir/irrXML.cpp.o"

# External object files for target IrrXML
IrrXML_EXTERNAL_OBJECTS =

assimp/contrib/irrXML/libIrrXML.a: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o
assimp/contrib/irrXML/libIrrXML.a: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/build.make
assimp/contrib/irrXML/libIrrXML.a: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libIrrXML.a"
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && $(CMAKE_COMMAND) -P CMakeFiles/IrrXML.dir/cmake_clean_target.cmake
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IrrXML.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/build: assimp/contrib/irrXML/libIrrXML.a

.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/build

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/requires: assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o.requires

.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/requires

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/clean:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML && $(CMAKE_COMMAND) -P CMakeFiles/IrrXML.dir/cmake_clean.cmake
.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/clean

assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/depend:
	cd /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template/assimp/contrib/irrXML /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML /home/6im2/bmantova/Documents/CPP-S3/GLImac-Template-build/assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : assimp/contrib/irrXML/CMakeFiles/IrrXML.dir/depend

