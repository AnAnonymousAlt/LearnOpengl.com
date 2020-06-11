#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>



enum class ERROR_TYPE
{
	Nullptr, LinkError, CompileError
};

// Print error info. use Debugger::print
// Automatically add function and file
#define perr(info, error) \
Debugger::print(info, error, __FUNCTION__, __LINE__, __FILE__);


class Debugger
{
public:

	static void print ( const char *, ERROR_TYPE, const char *, int, const char * );
private:
	static std::string errorTypeTranslater ( ERROR_TYPE );
};
