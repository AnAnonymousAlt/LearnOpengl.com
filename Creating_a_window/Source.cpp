#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>

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