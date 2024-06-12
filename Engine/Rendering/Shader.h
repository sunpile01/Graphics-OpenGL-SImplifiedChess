#ifndef __Shader_H
#define __Shader_H
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
class Shader
{
private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;
    GLint GetUniformLocation(const std::string& name);
    void CompileShader(GLenum shaderType, const std::string& shaderSource);
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void setInt(const std::string& name, const bool boolean);
    void setUniformFloat2(const std::string& name, const glm::vec2& vector);
    void SetUniform4fVector(const std::string& name, const glm::vec4& vector);
    void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
    inline GLuint getShaderProgram() const { return ShaderProgram; }
};
#endif

