#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>


enum class ERROR_TYPE
{
	Nullptr, LinkError, CompileError, FileNotExit, InvalidShader, EmptyString
};

// Print error info. use Debugger::print
// Automatically add function and file
#define perr(info, error) \
Debugger::print(info, error, __FUNCTION__, __LINE__, __FILE__);exit ( EXIT_FAILURE )


constexpr void *bufferOffset ( int a )
{
	return ( void * ) a;
}

class Debugger
{
public:

	static void print ( const char *, ERROR_TYPE, const char *, int, const char * );
	static void print ( char *info, ERROR_TYPE error,
						const char *funcName, int line, const char *fileName );
private:
	static std::string errorTypeTranslater ( ERROR_TYPE );
};

/// <summary>
/// Load file to string
/// </summary>
/// <param name="filename">file name path</param>
/// <param name="length">length of the file</param>
/// <returns>string in the file</returns>
std::string fileloader ( const char *filename, GLint *length);

/// <summary>
/// Load Shader file and compile
/// </summary>
/// <param name="shader">created shader name</param>
/// <param name="filename">file name path</param>
void shaderloader ( GLuint shader, const char *filename );

/// <summary>
/// Return size of the GL type
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
size_t typeSize ( GLenum );