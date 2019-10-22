cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(nenserver VERSION 0.1 LANGUAGES CXX)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make sure -lpthread is pulled in
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# pull in Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)

# Add subdirs
add_subdirectory("Chipmunk2D")
add_subdirectory("nenserver")
add_subdirectory("SFML")

