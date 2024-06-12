#ifndef IndexBuffer_H
#define IndexBuffer_H
#include "glad/glad.h"


class IndexBuffer {

private:
	GLuint IndexBufferID;
	GLuint Count;

public:
	IndexBuffer(GLuint* indices, GLsizei count);
	IndexBuffer(const void* indices, GLsizei count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;
	inline GLuint GetCount() const { return Count; }
	inline GLuint GetIndexBufferID() const { return IndexBufferID; }
};
#endif
