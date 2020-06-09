#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

enum class ERROR_TYPE
{
	Nullptr
};

class Debugger
{
public:
	static void print ( const char *, ERROR_TYPE, const char *, const char * );
private:
	static std::string errorTypeTranslater ( ERROR_TYPE );
};
