cmake_minimum_required(VERSION 3.15)

add_library(GLFWApplication GLFWApplication.cpp GLFWApplication.h)
add_library(Engine::GLFWApplication ALIAS GLFWApplication)
target_include_directories(GLFWApplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(GLFWApplication PUBLIC glad glfw TCLAP Rendering)


