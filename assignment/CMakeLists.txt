cmake_minimum_required(VERSION 3.15)

project (assignment)
add_executable(
	assignment
	Assignment.cpp
	AssignmentApplication.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE GLFWApplication)
target_link_libraries(${PROJECT_NAME} PRIVATE GeometricTools)
target_link_libraries(${PROJECT_NAME} PRIVATE Camera)
target_link_libraries(${PROJECT_NAME} PRIVATE Rendering)

add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/cube_texture.png
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/cube_texture.png
)
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/floor_texture.png 
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/floor_texture.png
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
	TEXTURE_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/")

target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)



