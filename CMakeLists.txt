cmake_minimum_required(VERSION 3.15) # Indicate CMake, which version is required (minimum) [5]
project(Group_39)				     # Sets up the name of the project [6]

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Fix the output directory for the archive artifacts [8]
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Fix the output directory for libraries [9]
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Fix the output directory for runtime files [10]
add_subdirectory(External/tclap)
add_subdirectory(External/glad)
add_subdirectory(External/glfw)
add_subdirectory(External/glm)
add_subdirectory(External/stb)
add_subdirectory(Engine/GLFWApplication)
add_subdirectory(Engine/GeometricTools)
add_subdirectory(Engine/Rendering)
add_subdirectory(Engine/Camera)
add_subdirectory(assignment)


