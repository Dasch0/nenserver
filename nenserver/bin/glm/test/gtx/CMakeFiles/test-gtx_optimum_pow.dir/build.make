# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /home/das/git/nenserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/das/git/nenserver/nenserver/bin

# Include any dependencies generated for this target.
include glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/depend.make

# Include the progress variables for this target.
include glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/progress.make

# Include the compile flags for this target's objects.
include glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/flags.make

glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o: glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/flags.make
glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o: ../../glm/test/gtx/gtx_optimum_pow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtx && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o -c /home/das/git/nenserver/glm/test/gtx/gtx_optimum_pow.cpp

glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.i"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtx && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/das/git/nenserver/glm/test/gtx/gtx_optimum_pow.cpp > CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.i

glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.s"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtx && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/das/git/nenserver/glm/test/gtx/gtx_optimum_pow.cpp -o CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.s

# Object files for target test-gtx_optimum_pow
test__gtx_optimum_pow_OBJECTS = \
"CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o"

# External object files for target test-gtx_optimum_pow
test__gtx_optimum_pow_EXTERNAL_OBJECTS =

glm/test/gtx/test-gtx_optimum_pow: glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/gtx_optimum_pow.cpp.o
glm/test/gtx/test-gtx_optimum_pow: glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/build.make
glm/test/gtx/test-gtx_optimum_pow: glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-gtx_optimum_pow"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-gtx_optimum_pow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/build: glm/test/gtx/test-gtx_optimum_pow

.PHONY : glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/build

glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/clean:
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtx && $(CMAKE_COMMAND) -P CMakeFiles/test-gtx_optimum_pow.dir/cmake_clean.cmake
.PHONY : glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/clean

glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/depend:
	cd /home/das/git/nenserver/nenserver/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/das/git/nenserver /home/das/git/nenserver/glm/test/gtx /home/das/git/nenserver/nenserver/bin /home/das/git/nenserver/nenserver/bin/glm/test/gtx /home/das/git/nenserver/nenserver/bin/glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glm/test/gtx/CMakeFiles/test-gtx_optimum_pow.dir/depend

