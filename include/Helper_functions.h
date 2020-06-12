#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>


enum class ERROR_TYPE
{
	Nullptr, LinkError, CompileError, FileNotExit
};

// Print error info. use Debugger::print
// Automatically add function and file
#define perr(info, error) \
Debugger::print(info, error, __FUNCTION__, __LINE__, __FILE__);


constexpr void *bufferOffset ( int a )
{
	return ( void * ) a;
}

class Debugger
{
public:

	static void print ( const char *, ERROR_TYPE, const char *, int, const char * );
private:
	static std::string errorTypeTranslater ( ERROR_TYPE );
};

/// <summary>
/// Loadfile
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
std::string fileloader ( const char *, GLint * );

/// <summary>
/// 
/// </summary>
/// <param name="shader"></param>
/// <param name="filename"></param>
void shaderloader ( GLuint shader, const char *filename );

/// <summary>
/// Return size of the GL type
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
size_t typeSize ( GLenum );