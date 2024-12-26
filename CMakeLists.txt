# Minimum required CMake version
cmake_minimum_required(VERSION 3.18)

# Project name and supported languages
project(SPH_Simulation LANGUAGES CXX CUDA)

# Set C++ and CUDA standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

add_subdirectory(libs/glfw-3.4)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glfw-3.4/include)

# Set the source files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.cu)
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c)

# Add the executable
add_executable(SPH_Simulation ${SOURCE_FILES} ${GLAD_SRC})

# Enable CUDA separable compilation
set_target_properties(SPH_Simulation PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(SPH_Simulation PRIVATE glfw3dll OpenGL::GL)

# Enable CUDA debug info in Debug mode
set_target_properties(SPH_Simulation PROPERTIES CUDA_DEBUGGER_ON_DEVICE $<$<CONFIG:DEBUG>:ON>)
