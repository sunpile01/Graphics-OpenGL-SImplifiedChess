#ifndef __RenderCommands_H
#define __RenderCommands_H
#include "glad/glad.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <glm/glm.hpp>

namespace RenderCommands
{
	//Clears the color and depth buffers
	inline void Clear(GLuint mode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) { glClear(mode); }
	inline void SetPolygonMode(GLenum face, GLenum mode) { glPolygonMode(face, mode); } 
	
	//Draws elements bound by vertex array object
	inline void DrawIndex(const std::shared_ptr<VertexArray>& vao, GLenum primitive) 
							{ glDrawElements(primitive, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); }

	//sets background color to the vec4 parameter
	inline void SetClearColor(const glm::vec4 clearColor) 
					{ glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]); }

	inline void SetWireframeMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }   //Sets wireframe mode
	inline void SetSolidMode() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }		//Polygons are filled
}


#endif