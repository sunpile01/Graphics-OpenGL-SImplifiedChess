/**
* @file VertexArray.cpp
* 
* @brief Possibility for creating, binding and deleting a vertex array.
*		 Also adding vertexBuffers and indexBuffers to the vertex array.
* 
* @author Aleksander Solhaug
*/
#include "VertexArray.h"

/**
* @brief Generates the vertexArray and binds it
*/
VertexArray::VertexArray() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

/**
* @brief Deletes the vertexArray and disables it
*/
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &VertexArrayID);
	glDisableVertexAttribArray(0);
}

/**
* @brief Binds the vertex array
*/
void VertexArray::Bind() const
{
	glBindVertexArray(VertexArrayID);
}

/**
* @brief Unbinds the vertex array
*/
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

/**
* @brief Adds the vertex buffer and its layout to the vertex array
* 
* @param vertexBuffer - vertexBuffer to be added to the vertex array
* @param layout - layout of the vertex buffer
*/
void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) {

	VertexBuffers.push_back(vertexBuffer);
	vertexBuffer->Bind();
	const auto& attributes = layout.GetAttributes();

	for (GLint i = 0; i < attributes.size(); i++) {
		const auto& attribute = attributes[i];
		//Sets all the attributs of the vertex array based on the layout of the vertex buffer
		glVertexAttribPointer(i, 
			ShaderDataTypeComponentCount(attribute.Type), 
			ShaderDataTypeToOpenGLBaseType(attribute.Type),
			attribute.Normalized, layout.GetStride(), 
			(const void*) attribute.Offset);

		glEnableVertexAttribArray(i);
	}
}



void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
	IdxBuffer = indexBuffer;
	//Binding the indexbuffer to the vertexarray
	IdxBuffer->bind();
}

