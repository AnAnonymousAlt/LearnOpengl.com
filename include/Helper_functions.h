#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

constexpr int ZERO = 0;

/// <summary>
/// use vec4 set clear color
/// </summary>
/// <param name="color"></param>
void glClearColorfv ( glm::vec4 color );

void glUniformRGBA ( GLint location, glm::vec4 color );


class Color
{
public:
	// https://web.archive.org/web/20180301041827/https://prideout.net/archive/colors.php#Sample
	static const glm::vec4 aliceblue;
	static const glm::vec4 antiquewhite;
	static const glm::vec4 aqua;
	static const glm::vec4 aquamarine;
	static const glm::vec4 azure;
	static const glm::vec4 beige;
	static const glm::vec4 bisque;
	static const glm::vec4 black;
	static const glm::vec4 blanchedalmond;
	static const glm::vec4 blue;
	static const glm::vec4 blueviolet;
	static const glm::vec4 brown;
	static const glm::vec4 burlywood;
	static const glm::vec4 cadetblue;
	static const glm::vec4 chartreuse;
	static const glm::vec4 chocolate;
	static const glm::vec4 coral;
	static const glm::vec4 cornflowerblue;
	static const glm::vec4 cornsilk;
	static const glm::vec4 crimson;
	static const glm::vec4 cyan;
	static const glm::vec4 darkblue;
	static const glm::vec4 darkcyan;
	static const glm::vec4 darkgoldenrod;
	static const glm::vec4 darkgray;
	static const glm::vec4 darkgreen;
	static const glm::vec4 darkgrey;
	static const glm::vec4 darkkhaki;
	static const glm::vec4 darkmagenta;
	static const glm::vec4 darkolivegreen;
	static const glm::vec4 darkorange;
	static const glm::vec4 darkorchid;
	static const glm::vec4 darkred;
	static const glm::vec4 darksalmon;
	static const glm::vec4 darkseagreen;
	static const glm::vec4 darkslateblue;
	static const glm::vec4 darkslategray;
	static const glm::vec4 darkslategrey;
	static const glm::vec4 darkturquoise;
	static const glm::vec4 darkviolet;
	static const glm::vec4 deeppink;
	static const glm::vec4 deepskyblue;
	static const glm::vec4 dimgray;
	static const glm::vec4 dimgrey;
	static const glm::vec4 dodgerblue;
	static const glm::vec4 firebrick;
	static const glm::vec4 floralwhite;
	static const glm::vec4 forestgreen;
	static const glm::vec4 fuchsia;
	static const glm::vec4 gainsboro;
	static const glm::vec4 ghostwhite;
	static const glm::vec4 gold;
	static const glm::vec4 goldenrod;
	static const glm::vec4 gray;
	static const glm::vec4 green;
	static const glm::vec4 greenyellow;
	static const glm::vec4 grey;
	static const glm::vec4 honeydew;
	static const glm::vec4 hotpink;
	static const glm::vec4 indianred;
	static const glm::vec4 indigo;
	static const glm::vec4 ivory;
	static const glm::vec4 khaki;
	static const glm::vec4 lavender;
	static const glm::vec4 lavenderblush;
	static const glm::vec4 lawngreen;
	static const glm::vec4 lemonchiffon;
	static const glm::vec4 lightblue;
	static const glm::vec4 lightcoral;
	static const glm::vec4 lightcyan;
	static const glm::vec4 lightgoldenrodyellow;
	static const glm::vec4 lightgray;
	static const glm::vec4 lightgreen;
	static const glm::vec4 lightgrey;
	static const glm::vec4 lightpink;
	static const glm::vec4 lightsalmon;
	static const glm::vec4 lightseagreen;
	static const glm::vec4 lightskyblue;
	static const glm::vec4 lightslategray;
	static const glm::vec4 lightslategrey;
	static const glm::vec4 lightsteelblue;
	static const glm::vec4 lightyellow;
	static const glm::vec4 lime;
	static const glm::vec4 limegreen;
	static const glm::vec4 linen;
	static const glm::vec4 magenta;
	static const glm::vec4 maroon;
	static const glm::vec4 mediumaquamarine;
	static const glm::vec4 mediumblue;
	static const glm::vec4 mediumorchid;
	static const glm::vec4 mediumpurple;
	static const glm::vec4 mediumseagreen;
	static const glm::vec4 mediumslateblue;
	static const glm::vec4 mediumspringgreen;
	static const glm::vec4 mediumturquoise;
	static const glm::vec4 mediumvioletred;
	static const glm::vec4 midnightblue;
	static const glm::vec4 mintcream;
	static const glm::vec4 mistyrose;
	static const glm::vec4 moccasin;
	static const glm::vec4 navajowhite;
	static const glm::vec4 navy;
	static const glm::vec4 oldlace;
	static const glm::vec4 olive;
	static const glm::vec4 olivedrab;
	static const glm::vec4 orange;
	static const glm::vec4 orangered;
	static const glm::vec4 orchid;
	static const glm::vec4 palegoldenrod;
	static const glm::vec4 palegreen;
	static const glm::vec4 paleturquoise;
	static const glm::vec4 palevioletred;
	static const glm::vec4 papayawhip;
	static const glm::vec4 peachpuff;
	static const glm::vec4 peru;
	static const glm::vec4 pink;
	static const glm::vec4 plum;
	static const glm::vec4 powderblue;
	static const glm::vec4 purple;
	static const glm::vec4 red;
	static const glm::vec4 rosybrown;
	static const glm::vec4 royalblue;
	static const glm::vec4 saddlebrown;
	static const glm::vec4 salmon;
	static const glm::vec4 sandybrown;
	static const glm::vec4 seagreen;
	static const glm::vec4 seashell;
	static const glm::vec4 sienna;
	static const glm::vec4 silver;
	static const glm::vec4 skyblue;
	static const glm::vec4 slateblue;
	static const glm::vec4 slategray;
	static const glm::vec4 slategrey;
	static const glm::vec4 snow;
	static const glm::vec4 springgreen;
	static const glm::vec4 steelblue;
	static const glm::vec4 tan;
	static const glm::vec4 teal;
	static const glm::vec4 thistle;
	static const glm::vec4 tomato;
	static const glm::vec4 turquoise;
	static const glm::vec4 violet;
	static const glm::vec4 wheat;
	static const glm::vec4 white;
	static const glm::vec4 whitesmoke;
	static const glm::vec4 yellow;
	static const glm::vec4 yellowgreen;
};

constexpr int ClearBit = 0;

enum VEC_SIZE
{
	VEC1 = 1, VEC2 = 2, VEC3 = 3, VEC4 = 4
};

/// <summary>
/// Enum of Error Type
/// </summary>
enum class ERROR_TYPE
{
	NullPtr, LinkError, CompileError, FileNotExit,
	InvalidShader, InvalidProgram, EmptyString, EmptyMatrixVertex,
	GLFWFail, WindowFail
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


class Matrix
{
public:
	Matrix ();
	bool addName ( std::string name );
	bool addVertex ( glm::vec4 vertex );
	int vSize ();
	int eSize ();
	std::string getName ();
	std::vector<glm::vec4> getVector ();
	glm::vec4 getVertex ( int num );
	void *getVAddress ();
	void *getEAddress ();
	glm::ivec3 getElement ( int num );
	bool addElement ( glm::uvec3 element );
	std::vector< glm::uvec3 > getElementArray ();
	std::string name;
	std::vector<glm::vec4> vertices;
	std::vector< glm::uvec3 > elements;
	
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
	std::vector< Matrix > matrixes;
	std::string name;
};

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
						const char *funcname, int line, const char *filename );
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
	static void shaderLoader ( GLuint shader, const char *filename );

	/// <summary>
	/// 
	/// </summary>
	/// <param name="shader"></param>
	static void shaderCompiler ( GLuint shader );


	static void shaderAttacher ( GLuint program, GLuint shader );


	static void shaderWorker ( GLuint program, GLuint shader, const char *filename );


	/// <summary>
	/// 
	/// </summary>
	/// <param name="matrixes"></param>
	/// <param name="filename"></param>
	static Model vertexLoader ( const char *filename );


	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="filename"></param>
	static void elementLoader ( Model *model, const char *filename );


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



