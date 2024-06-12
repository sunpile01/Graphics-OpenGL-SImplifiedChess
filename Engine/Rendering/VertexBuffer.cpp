/**
* @file VertexBuffer.cpp
*
* Possibility for creating, binding, deleting vertex buffers.
* Also possible to change data within an existing vertex buffer.
* 
* @author Aleksander Solhaug
*/

#include "VertexBuffer.h"

/**
* @brief Genereates and fills the vertex buffer with data
* 
* @param data - The data the vertex buffer wil contain
* @param size - the size of the data 
*/
VertexBuffer::VertexBuffer(const void* data, GLuint size) {
   
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/**
* @brief Deletes the vertex buffer
* 
*/
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &VertexBufferID);
}

/**
* @brief Binds the vertex buffer
*
*/
void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
} 

/**
* @brief Unbinds the vertex buffer
*
*/
void VertexBuffer::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
* @brief Updates a subset of data from the offset within the buffer
* 
* @param offset - The offset to where the existing data will be replaced
* @param data - The data to replace the current data
*/
void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}



