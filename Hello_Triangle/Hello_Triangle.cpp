#include "../include/Helper_functions.h"



enum VAO_ID
{
	H, E, numVAOs
};

enum BUFFER_ID
{
	HArray, EArray, HElement, EElement, numBuffers
};

enum ATTRIB_ID
{
	vPosition
};


GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];

enum PROGRAM_ID
{
	Program1, Program2, numPrograms
};
enum SHADER_ID
{
	VShader, FShader1, FShader2, numShaders
};
GLuint programs[numPrograms];
GLuint shaders[numShaders];
Model mo;
int success;
char infoLog[512];
#define LOGSIZE 512

/// <summary>
/// resize window
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void framebufferSizeCallback ( GLFWwindow *window, int width, int height );

/// <summary>
/// esc
/// </summary>
/// <param name="window"></param>
void processInput ( GLFWwindow *window );



void
init ()
{

	mo = Helper::vertexLoader ( "Hello.vi" );
	Helper::elementLoader ( &mo, "Hello.ei" );
	Matrix maH = mo.matrixes[H];
	Matrix maE = mo.matrixes[E];

	programs[Program1] = glCreateProgram ();
	shaders[VShader] = glCreateShader ( GL_VERTEX_SHADER );
	shaders[FShader1] = glCreateShader ( GL_FRAGMENT_SHADER );
	Helper::shaderloader ( shaders[VShader], "vertex.glsl" );
	Helper::shaderloader ( shaders[FShader1], "fragment.glsl" );

	glAttachShader ( programs[Program1], shaders[VShader] );
	glAttachShader ( programs[Program1], shaders[FShader1] );
	glLinkProgram ( programs[Program1] );
	glGetProgramiv ( programs[Program1], GL_LINK_STATUS, &success );
	if ( !success )
	{
		glGetProgramInfoLog ( programs[Program1], LOGSIZE, NULL, infoLog );
		DEBUGP ( infoLog, ERROR_TYPE::LinkError );
	}

	programs[Program2] = glCreateProgram ();
	shaders[FShader2] = glCreateShader ( GL_FRAGMENT_SHADER );
	Helper::shaderloader ( shaders[FShader2], "fragment2.glsl" );

	glAttachShader ( programs[Program2], shaders[VShader] );
	glAttachShader ( programs[Program2], shaders[FShader2] );
	glLinkProgram ( programs[Program2] );
	glGetProgramiv ( programs[Program2], GL_LINK_STATUS, &success );
	if ( !success )
	{
		glGetProgramInfoLog ( programs[Program2], LOGSIZE, NULL, infoLog );
		DEBUGP ( infoLog, ERROR_TYPE::LinkError );
	}
	for ( int i = 0; i < numShaders; i++ )
	{
		glDeleteShader ( shaders[i] );
	}

	// VAOs
	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );

	// H
	glBindVertexArray ( VAOs[H] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[HArray] );
	glNamedBufferStorage ( buffers[HArray],
						   Helper::typeSize ( GL_FLOAT_VEC4 ) * maH.vSize (),
						   maH.getVAddress (), GL_DYNAMIC_STORAGE_BIT );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffers[HElement] );
	glNamedBufferStorage ( buffers[HElement],
						   Helper::typeSize ( GL_UNSIGNED_INT_VEC3 ) * maH.eSize (),
						   maH.getEAddress (),
						   GL_DYNAMIC_STORAGE_BIT );

	glVertexAttribPointer ( vPosition, VEC_SIZE::VEC4, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ), bufferOffset ( 0 ) );
	glEnableVertexAttribArray ( vPosition );

	glBindVertexArray ( ClearBit );
	glBindBuffer ( GL_ARRAY_BUFFER, ClearBit );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ClearBit );


	// E
	glBindVertexArray ( VAOs[E] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[EArray] );
	glNamedBufferStorage ( buffers[EArray],
						   Helper::typeSize ( GL_FLOAT_VEC4 ) * maE.vSize (),
						   maE.getVAddress (), GL_DYNAMIC_STORAGE_BIT );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffers[EElement] );
	glNamedBufferStorage ( buffers[EElement],
						   Helper::typeSize ( GL_UNSIGNED_INT_VEC3 ) * maE.eSize (),
						   maE.getEAddress (), GL_DYNAMIC_STORAGE_BIT );
	glVertexAttribPointer ( vPosition, VEC_SIZE::VEC4, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ), bufferOffset ( 0 ) );
	glEnableVertexAttribArray ( vPosition );

	glBindVertexArray ( ClearBit );
	glBindBuffer ( GL_ARRAY_BUFFER, ClearBit );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ClearBit );


	// glClearColor ( 0.1f, 0.0f, 0.1f, 1.0f );
	glClearColorfv ( Color::darkcyan );

}

void
display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );


	glUseProgram ( programs[Program1] );
	glBindVertexArray ( VAOs[H] );
	//glDrawArrays ( GL_TRIANGLES, 0, 4 );   
	glDrawElements ( GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0 );

	glUseProgram ( programs[Program2] );

	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
	glBindVertexArray ( VAOs[E] );
	glDrawElements ( GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0 );

	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

}

int
main ( int argc, char **argv )
{
	glfwInit ();

	#ifdef __APPLE__
	glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	#endif

	GLFWwindow *window = glfwCreateWindow ( 640, 480, "Hello Triangle", NULL, NULL );
	DEBUG ( window == NULL, ERROR_TYPE::GLFWFail );

	glfwMakeContextCurrent ( window );
	glfwSetFramebufferSizeCallback ( window, framebufferSizeCallback );


	gl3wInit ();
	init ();

	while ( !glfwWindowShouldClose ( window ) )
	{
		processInput ( window );
		display ();
		glfwSwapBuffers ( window );
		glfwPollEvents ();
	}
	glDeleteVertexArrays ( numVAOs, VAOs );
	glDeleteBuffers ( numBuffers, buffers );
	for ( int i = 0; i < numPrograms; i++ )
	{
		glDeleteProgram ( programs[i] );
	}


	glfwDestroyWindow ( window );

	glfwTerminate ();
	return 0;
}


void processInput ( GLFWwindow *window )
{
	if ( glfwGetKey ( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose ( window, true );
	}
}

void framebufferSizeCallback ( GLFWwindow *window, int width, int height )
{
	glViewport ( 0, 0, width, height );
}