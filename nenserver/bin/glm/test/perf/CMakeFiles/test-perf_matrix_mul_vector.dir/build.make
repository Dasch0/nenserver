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
include glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/depend.make

# Include the progress variables for this target.
include glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/progress.make

# Include the compile flags for this target's objects.
include glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/flags.make

glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o: glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/flags.make
glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o: ../../glm/test/perf/perf_matrix_mul_vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/perf && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o -c /home/das/git/nenserver/glm/test/perf/perf_matrix_mul_vector.cpp

glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.i"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/perf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/das/git/nenserver/glm/test/perf/perf_matrix_mul_vector.cpp > CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.i

glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.s"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/perf && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/das/git/nenserver/glm/test/perf/perf_matrix_mul_vector.cpp -o CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.s

# Object files for target test-perf_matrix_mul_vector
test__perf_matrix_mul_vector_OBJECTS = \
"CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o"

# External object files for target test-perf_matrix_mul_vector
test__perf_matrix_mul_vector_EXTERNAL_OBJECTS =

glm/test/perf/test-perf_matrix_mul_vector: glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/perf_matrix_mul_vector.cpp.o
glm/test/perf/test-perf_matrix_mul_vector: glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/build.make
glm/test/perf/test-perf_matrix_mul_vector: glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/das/git/nenserver/nenserver/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-perf_matrix_mul_vector"
	cd /home/das/git/nenserver/nenserver/bin/glm/test/perf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-perf_matrix_mul_vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/build: glm/test/perf/test-perf_matrix_mul_vector

.PHONY : glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/build

glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/clean:
	cd /home/das/git/nenserver/nenserver/bin/glm/test/perf && $(CMAKE_COMMAND) -P CMakeFiles/test-perf_matrix_mul_vector.dir/cmake_clean.cmake
.PHONY : glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/clean

glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/depend:
	cd /home/das/git/nenserver/nenserver/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/das/git/nenserver /home/das/git/nenserver/glm/test/perf /home/das/git/nenserver/nenserver/bin /home/das/git/nenserver/nenserver/bin/glm/test/perf /home/das/git/nenserver/nenserver/bin/glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glm/test/perf/CMakeFiles/test-perf_matrix_mul_vector.dir/depend

