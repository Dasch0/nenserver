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
include glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/depend.make

# Include the progress variables for this target.
include glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/progress.make

# Include the compile flags for this target's objects.
include glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/flags.make

glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o: glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/flags.make
glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o: ../../glm/test/ext/ext_matrix_relational.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/ext && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o -c /home/das/git/nenserver/glm/test/ext/ext_matrix_relational.cpp

glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.i"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/ext && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/das/git/nenserver/glm/test/ext/ext_matrix_relational.cpp > CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.i

glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.s"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/ext && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/das/git/nenserver/glm/test/ext/ext_matrix_relational.cpp -o CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.s

# Object files for target test-ext_matrix_relational
test__ext_matrix_relational_OBJECTS = \
"CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o"

# External object files for target test-ext_matrix_relational
test__ext_matrix_relational_EXTERNAL_OBJECTS =

glm/test/ext/test-ext_matrix_relational: glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/ext_matrix_relational.cpp.o
glm/test/ext/test-ext_matrix_relational: glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/build.make
glm/test/ext/test-ext_matrix_relational: glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-ext_matrix_relational"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/ext && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-ext_matrix_relational.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/build: glm/test/ext/test-ext_matrix_relational

.PHONY : glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/build

glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/clean:
	cd /home/das/git/nenserver/nenserver/bin/glm/test/ext && $(CMAKE_COMMAND) -P CMakeFiles/test-ext_matrix_relational.dir/cmake_clean.cmake
.PHONY : glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/clean

glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/depend:
	cd /home/das/git/nenserver/nenserver/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/das/git/nenserver /home/das/git/nenserver/glm/test/ext /home/das/git/nenserver/nenserver/bin /home/das/git/nenserver/nenserver/bin/glm/test/ext /home/das/git/nenserver/nenserver/bin/glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glm/test/ext/CMakeFiles/test-ext_matrix_relational.dir/depend

