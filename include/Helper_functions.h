#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>



class Matrix
{
public:
	Matrix ();
	bool addName ( std::string name );
	bool addVertex ( glm::vec4 vertex );
	int length ();
	std::string getName ();
	std::vector<glm::vec4> getVector ();
	glm::vec4 getVertex ( int num );
	void *getPointer ();
private:
	std::string name;
	std::vector<glm::vec4> vertices;
};


class Model
{
public:
	Model ();
	int length ();
	Matrix getMatrix ( int number );
	std::string getName ();
	bool addMatrix ( Matrix matrix );
	bool addName ( std::string name );
	std::vector< Matrix > getModel ();
private:
	std::vector< Matrix > matrixes;
	std::string name;
};


/// <summary>
/// Enum of Error Type
/// </summary>
enum class ERROR_TYPE
{
	NullPtr, LinkError, CompileError, FileNotExit,
	InvalidShader, EmptyString, EmptyMatrixVertex
};

/// DEBUG 
#define DEBUG(errorCondition, code) \
if ( errorCondition ) \
{ \
	Helper::print ( "", code, __FUNCTION__, __LINE__, __FILE__ );  \
	exit ( EXIT_FAILURE ); \
} \

/// Debug EXtend 1
#define DEBUGE(errorCondition, error, code)\
if ( errorCondition ) \
{ \
	Helper::print ( error, code, __FUNCTION__, __LINE__, __FILE__ );  \
	exit ( EXIT_FAILURE ); \
} \

/// Debug Print
#define DEBUGP(error, code)\
Helper::print ( error, code, __FUNCTION__, __LINE__, __FILE__ );  \
exit ( EXIT_FAILURE ); \

/// <summary>
/// Buffer offset
/// </summary>
/// <param name="a">a void pointer</param>
/// <returns>void pointer</returns>
constexpr void *bufferOffset ( void *p )
{
	return ( void * ) p;
}

/// <summary>
/// Helper class: print
/// </summary>
class Helper
{
public:

	/// <summary>
	/// error Printer
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	static void print ( const char *, ERROR_TYPE, const char *, int, const char * );
	static void print ( char *info, ERROR_TYPE error,
						const char *funcName, int line, const char *fileName );
	/// <summary>
	/// Load file to string
	/// </summary>
	/// <param name="filename">file name path</param>
	/// <param name="length">length of the file</param>
	/// <returns>string in the file</returns>
	static std::string fileLoader ( const char *filename, GLint *length );

	/// <summary>
	/// Load Shader file and compile
	/// </summary>
	/// <param name="shader">created shader name</param>
	/// <param name="filename">file name path</param>
	static void shaderloader ( GLuint shader, const char *filename );

	/// <summary>
	/// 
	/// </summary>
	/// <param name="matrixes"></param>
	/// <param name="filename"></param>
	static Model vertexLoader ( const char *filename );

	/// <summary>
	/// Return size of the GL type
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static size_t typeSize ( GLenum );
private:
	enum e
	{
		d
	};
	static std::string errorTranslater ( ERROR_TYPE );
};



