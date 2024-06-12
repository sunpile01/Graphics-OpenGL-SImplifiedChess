/**
* @file Shader.cpp
* 
* Possibilities for creating, binding and deleting shaders.
* Functions to upload various uniforms to the shaders.
* 
* @author Aleksander Solhaug
*/

#include "Shader.h"

/**
* @brief Compiles the Shader sent as parameter
* 
* @param shaderType - If its the veretx or fragment shader
* @param ShaderSource - The code within the shader
*/
void Shader::CompileShader(GLenum shaderType, const std::string& shaderSource)
{
	const GLchar* ShaderSource = shaderSource.c_str();
	int valid = 0;
	char message[512];											//Error message 
	if (shaderType == GL_VERTEX_SHADER) {
		VertexShader = glCreateShader(shaderType);
		glShaderSource(VertexShader, 1, &ShaderSource, NULL);	//Code source
		glCompileShader(VertexShader);
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &valid);
		if (valid == 0) {
			//Gets the error and stores it in the message variable
			glGetShaderInfoLog(VertexShader, 512, NULL, message);	
			std::cout << "Vertex Shader compilation failed\n" << message << std::endl;
		}
	}
	else {
		FragmentShader = glCreateShader(shaderType);
		glShaderSource(FragmentShader, 1, &ShaderSource, NULL);
		glCompileShader(FragmentShader);
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &valid);
		if (valid == 0) {
			glGetShaderInfoLog(FragmentShader, 512, NULL, message);
			std::cout << "Fragment shader compilation failed \n" << message << std::endl << shaderSource.c_str();
		}
	}
}

/**
* @brief Compiling, creating and attaching the shaders to the application
*	     
*/
Shader::Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
{
	ShaderProgram = glCreateProgram();

	CompileShader(GL_VERTEX_SHADER, vertexShaderSrc);
	CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

/**
* @brief unbinding the shader program
*/
Shader::~Shader()
{
	glUseProgram(0);
}

/**
* @brief Binding the shader program
*/
void Shader::Bind() const
{
	glUseProgram(ShaderProgram);
}

/**
* @brief Unbinding the shader program
*/
void Shader::Unbind() const
{
	glUseProgram(0);
}

/**
* @brief uploading an int to the shader
* 
* @param name - Name of the variable in the shader
* @param boolean - 0 or 1
*/
void Shader::setInt(const std::string& name, const bool boolean)
{
	glUniform1i(GetUniformLocation(name), boolean);
}

/**
* @brief uploading a vector with 2 floats to the shader
*
* @param name - Name of the variable in the shader
* @param vector - vector with the 2 floats to be uploaded
*/
void Shader::setUniformFloat2(const std::string& name, const glm::vec2& vector)
{
	glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

/**
* @brief uploading a vector with 4 floats to the shader
*
* @param name - Name of the variable in the shader
* @param vector - vector with the 4 floats to be uploaded
*/
void Shader::SetUniform4fVector(const std::string& name, const glm::vec4& vector) 
{
	glUniform4f(GetUniformLocation(name), vector[0], vector[1], vector[2], vector[3]);
}

/**
* @brief uploading a 4*4 matrix with floats to the shader
*
* @param name - Name of the variable in the shader
* @param matrix - matrix with the floats to be uploaded
*/
void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix) 
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

/**
* @brief gets the location of the uniform ton be uploaded
* 
* @param name - Name of the variable in the shader
* @return location - location of the uniform
*/
GLint Shader::GetUniformLocation(const std::string& name) 
{
	GLint location = glGetUniformLocation(ShaderProgram, name.c_str());
	if (location == -1)
		std::cout << "\n\tUniform " << name << " does not  exist!\n";
	else 
		Bind();
	return location;
}
