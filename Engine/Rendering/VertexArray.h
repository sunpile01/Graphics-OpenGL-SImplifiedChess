#ifndef __VertexArray_H
#define __VertexArray_H
#include "glad/glad.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>
#include "IndexBuffer.h"

class VertexArray {

public:
	// Constructor & Destructor
	VertexArray();
	~VertexArray();

	// Bind vertex array
	void Bind() const;
	// Unbind vertex array
	void Unbind() const;

	// Add vertex buffer. This method utilizes the BufferLayout internal to 
	// the vertex buffer to set up the vertex attributes. Notice that 
	// this function opens for the definition of several vertex buffers.
	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout);
	// Set index buffer
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	//Get the index buffer
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return IdxBuffer; }
	
	
private:
	GLuint VertexArrayID;
	std::vector<std::shared_ptr<VertexBuffer>> VertexBuffers;
	std::shared_ptr<IndexBuffer> IdxBuffer;
	// Get the vertex buffers
	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return VertexBuffers; }
};

#endif