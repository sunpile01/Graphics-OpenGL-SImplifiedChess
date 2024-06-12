/**
* @file VertexArray.cpp
*
* @brief Possibility to create, bind and delete an indexBuffer 
* 
* @author Aleksander Solhaug
*/

#include "IndexBuffer.h"

/**
* @brief Generates the index buffer and fills it with the data sent from the parameters
* 
* @param indices - Indices that connects the vertices int he triangles
* @param count - Number of indices 
*/
IndexBuffer::IndexBuffer(GLuint *indices, GLsizei count) {
    Count = count;
    glGenBuffers(1, &IndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

/**
* @brief Generates the index buffer and fills it with the data sent from the parameters
* 
* @param indices - Indices that connects the vertices int he triangles
* @param count - Number of indices
*/
IndexBuffer::IndexBuffer(const void* indices, GLsizei count) {
    Count = count;
    glGenBuffers(1, &IndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

/**
* @brief Deletes the index buffer
*/
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &IndexBufferID);
}

/**
* @brief Binds the index buffer
*/
void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
}

/**
* @brief unbinds the index buffer
*/
void IndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}