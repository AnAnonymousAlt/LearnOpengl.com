#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Helperfunctions.h"

#include <iostream>
#include <fstream>
#include <string>

//enum ERROR_TYPE
//{
//	null
//};
//
//void bugOut (const char *string, int )

const char *fileloader ( const char *filename, GLint *length)
{
	if ( length == NULL )
	{
		std::cerr << "fileloader: length is NULL" << std::endl;
		exit ( EXIT_FAILURE );
	}
	if ( filename == NULL )
	{
		
	}
	std::ifstream fs ( filename );
	std::string s = std::string ( std::istreambuf_iterator<char> ( fs ), std::istreambuf_iterator<char> () );
	
	*length = s.length ();
	return s.c_str ();
}

/// <summary>
/// 
/// </summary>
/// <param name="shader">a created shader name</param>
/// <param name="filename">shader file name in const C string</param>
void shaderloader ( GLuint shader, const char *filename )
{
	GLint length;
	const char *text = fileloader ( filename, &length );
	glShaderSource ( shader, 1, &text, &length );
	glCompileShader ( shader );
	return;
}

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

void init ()
{
	glClearColor ( 1.0f, 0.1f, 0.3f, 1.0f );
}

void display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );

}

int
main ( int argc, char **argv )
{
	EC.out ();
	glfwInit ();
	
	GLFWwindow *window = glfwCreateWindow (640, 480, "Window", NULL, NULL);
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

	glViewport ( 0, 0, 640, 480 );
	glfwSetFramebufferSizeCallback ( window, frameBufferSizeCallback );

	while ( !glfwWindowShouldClose ( window ) )
	{
		// input
		processInput ( window );
		// rendering
		display ();
		// swap buffer
		glfwSwapBuffers (window);
		// check and call events
		glfwPollEvents ();
	}
	glfwDestroyWindow ( window );
	glfwTerminate ();
	return EXIT_SUCCESS;

}