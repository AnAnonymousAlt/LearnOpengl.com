#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// #include "../include/Helper_functions.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum VAO_ID
{
	Triangle, numVAOs
};

enum Buffer_ID
{
	ArrayBuffer, numBuffers
};

enum ATTRIB_ID
{
	vPosition
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];

const GLint numVertex = 3; // num of total vertices
const GLint numElement = 2; // num of element in a vector

void frameBufferSizeCallback ( GLFWwindow *window, int width, int height )
{
	glViewport ( 0, 0, width, height );

}

void processInput ( GLFWwindow *window )
{
	if ( glfwGetKey ( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
	{
		glfwSetWindowShouldClose ( window, true );
	}
}

GLfloat triangle[3][2] =
{
	{ 0.0, 0.0 },
	{ 0.3, 0.0 },
	{ 0.0, 0.3 }
};
void init ()
{
	GLuint program = glCreateProgram ();
	GLuint vShader = glCreateShader ( GL_VERTEX_SHADER );
	GLuint fShader = glCreateShader ( GL_FRAGMENT_SHADER );

	//const GLfloat triangle[numVertex][numElement] =
	//{
	//	{ -0.5f, -0.5f },
	//	{  0.5f, -0.5f },
	//	{ -0.5f,  0.5f }
	//};

	//glCreateVertexArrays ( numVAOs, VAOs );
	//glCreateBuffers ( numBuffers, buffers );

	//glBindVertexArray ( VAOs[Triangle] );

	//glBindBuffer ( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );
	
	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );

	ifstream vfs = ifstream ( "vertex.glsl" );
	string vs = string ( istreambuf_iterator<char> ( vfs ),
						 istreambuf_iterator<char> () );
	const char *vt = vs.c_str ();
	GLint vl = vs.length ();
	glShaderSource ( vShader, 1, &vt, &vl );
	glCompileShader ( vShader );

	ifstream ffs = ifstream ( "fragment.glsl" );
	string fs = string ( istreambuf_iterator<char> ( ffs ),
						 istreambuf_iterator<char> () );
	const char *ft = fs.c_str ();
	GLint fl = fs.length ();
	glShaderSource ( fShader, 1, &ft, &fl );
	glCompileShader ( fShader );

	//shaderloader ( vShader, "vertex.glsl" );
	//shaderloader ( fShader, "fragment.glsl" );

	glAttachShader ( program, vShader );
	glAttachShader ( program, fShader );
	glLinkProgram ( program );
	glUseProgram ( program );

	//glClearColor ( 0.0f, 0.1f, 0.3f, 1.0f );

	//glNamedBufferStorage ( buffers[ArrayBuffer], sizeof ( triangle ), &triangle, GL_DYNAMIC_STORAGE_BIT );
	///*glVertexAttribPointer ( vPosition, numElement, GL_FLOAT, GL_FALSE, 
	//						numVertex * typeSize(GL_FLOAT_VEC2), bufferOffset(0));*/
	//glVertexAttribPointer ( vPosition, numElement, GL_FLOAT, GL_FALSE,
	//						0, (void*) 0 );
	//glEnableVertexAttribArray ( vPosition );

	glBindVertexArray ( VAOs[Triangle] );
	glNamedBufferStorage ( buffers[ArrayBuffer], sizeof ( triangle ), &triangle, GL_DYNAMIC_STORAGE_BIT );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );

	glVertexAttribPointer ( vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *) ( 0 ) );
	glEnableVertexAttribArray ( vPosition );

}

void display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );

	glBindVertexArray ( VAOs[Triangle] );
	glDrawArrays ( GL_TRIANGLES, 0, 3 );
}

int
main ( int argc, char **argv )
{

	glfwInit ();

	GLFWwindow *window = glfwCreateWindow ( 640, 480, "Window", NULL, NULL );
	if ( window == NULL )
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate ();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent ( window );

	gl3wInit ();
	// variable init has to be put after glfwMakeContextCurrent call
	init ();

	// glViewport ( 0, 0, 640, 480 );
	// glfwSetFramebufferSizeCallback ( window, frameBufferSizeCallback );

	while ( !glfwWindowShouldClose ( window ) )
	{
		// input
		processInput ( window );
		// rendering
		display ();
		// swap buffer
		glfwSwapBuffers ( window );
		// check and call events
		glfwPollEvents ();
	}
	glfwDestroyWindow ( window );
	glfwTerminate ();
	return EXIT_SUCCESS;

}