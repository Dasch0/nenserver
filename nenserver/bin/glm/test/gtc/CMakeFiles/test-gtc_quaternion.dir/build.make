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
include glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/depend.make

# Include the progress variables for this target.
include glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/progress.make

# Include the compile flags for this target's objects.
include glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/flags.make

glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o: glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/flags.make
glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o: ../../glm/test/gtc/gtc_quaternion.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtc && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o -c /home/das/git/nenserver/glm/test/gtc/gtc_quaternion.cpp

glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.i"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtc && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/das/git/nenserver/glm/test/gtc/gtc_quaternion.cpp > CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.i

glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.s"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtc && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/das/git/nenserver/glm/test/gtc/gtc_quaternion.cpp -o CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.s

# Object files for target test-gtc_quaternion
test__gtc_quaternion_OBJECTS = \
"CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o"

# External object files for target test-gtc_quaternion
test__gtc_quaternion_EXTERNAL_OBJECTS =

glm/test/gtc/test-gtc_quaternion: glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/gtc_quaternion.cpp.o
glm/test/gtc/test-gtc_quaternion: glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/build.make
glm/test/gtc/test-gtc_quaternion: glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-gtc_quaternion"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-gtc_quaternion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/build: glm/test/gtc/test-gtc_quaternion

.PHONY : glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/build

glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/clean:
	cd /home/das/git/nenserver/nenserver/bin/glm/test/gtc && $(CMAKE_COMMAND) -P CMakeFiles/test-gtc_quaternion.dir/cmake_clean.cmake
.PHONY : glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/clean

glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/depend:
	cd /home/das/git/nenserver/nenserver/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/das/git/nenserver /home/das/git/nenserver/glm/test/gtc /home/das/git/nenserver/nenserver/bin /home/das/git/nenserver/nenserver/bin/glm/test/gtc /home/das/git/nenserver/nenserver/bin/glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glm/test/gtc/CMakeFiles/test-gtc_quaternion.dir/depend

