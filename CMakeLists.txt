cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(nenserver VERSION 0.1 LANGUAGES CXX)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make sure freetype is pulled in
find_package(Freetype REQUIRED)

# Make sure -lpthread is pulled in
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# disable lib tests
set(BUILD_TESTS OFF CACHE BOOL "disable tests" FORCE)
set(BUILD_DEMOS OFF CACHE BOOL "disable tests" FORCE)

# Add subdirs
add_subdirectory("nenserver")
add_subdirectory("lib/Chipmunk2D")
add_subdirectory("lib/SFML")
add_subdirectory("lib/libzmq")
add_subdirectory("lib/parallel-hashmap")

