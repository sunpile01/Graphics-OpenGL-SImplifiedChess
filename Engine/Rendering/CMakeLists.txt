cmake_minimum_required(VERSION 3.15)

project (Rendering)

add_library(Rendering IndexBuffer.h IndexBuffer.cpp 
			RenderCommands.h Shader.cpp Shader.h
			VertexArray.cpp VertexArray.h 
			VertexBuffer.cpp VertexBuffer.h 
			ShaderDataTypes.h  VertexBufferLayout.h
			TextureManager.cpp TextureManager.h)
add_library(Engine::Rendering ALIAS Rendering)
target_include_directories(Rendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Rendering PUBLIC glad glfw glm stb)
target_compile_features(Rendering PUBLIC cxx_std_17)

