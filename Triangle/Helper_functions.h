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
	void print ( ERROR_TYPE );
private:
	std::string errorTypeTranslater ( ERROR_TYPE );
}DB;
