#ifndef VertexBuffer_H
#define VertexBuffer_H
#include "glad/glad.h"
#include "VertexBufferLayout.h"

class VertexBuffer {

private:
	GLuint VertexBufferID;
	BufferLayout Layout;
public:
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const; //only a segment of the buffer
	inline GLuint GetVertexBufferID() const { return VertexBufferID; }
	// Set/Get buffer layout
	const BufferLayout& GetLayout() const { return Layout; }
	void SetLayout(const BufferLayout& layout) { Layout = layout; }
};
#endif