#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tclap/CmdLine.h>
#include <cstdlib>
#include <iostream>

class GLFWApplication
{
public:
	GLFWApplication(const std::string name, const std::string version);
	~GLFWApplication();

	//Argument parsing
	virtual unsigned int ParseArguments(int argc, char** argv); // Virtual function with default behavior.
	// Initialization 
	virtual unsigned Init(); // Virtual function with default behavior
	// Run function
	virtual unsigned Run() const = 0; // Pure virtual function, it must be redefined

protected:
	GLint m_height;
	GLint m_width;
	GLFWwindow* m_window;
	std::string m_name, m_version;
};


#endif