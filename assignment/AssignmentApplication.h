#ifndef AssignmentApplication_H_
#define AssignmentApplication_H_
#include <GLFWApplication.h>

class Assignment : public GLFWApplication {
public:
	Assignment(const std::string name, const std::string version);
	~Assignment();
	virtual unsigned int ParseArguments(int argc, char** argv);
	virtual unsigned Init();
	virtual unsigned Run() const override;
};

#endif