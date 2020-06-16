#include "../include/Helper_functions.h"


int screen_width = 640;
int screen_height = 480;
constexpr int ZERO = 0;

enum VAO_ID
{
	VAO0, numVAOs
};

enum Buffer_ID
{
	Buffer0, numBuffers
};

enum Program_ID
{
	Program0, numPrograms
};

enum Shader_ID
{
	VShader0, FShader0, numShaders
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];
GLuint programs[numPrograms];
GLuint shaders[numShaders];

void
framebufferSizeCallback ( GLFWwindow *window, int width, int height );


void
init ()
{
	glClearColorfv ( Color: . :darkcyan );
}

void
processInput ( GLFWwindow *window );

void
display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );
}

int
main ( int argc, char **argv )
{
	glfwInit ();

	#ifdef __APPLE__
	glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	#endif

	GLFWwindow *window = glfwCreateWindow ( screen_width, screen_height, "Titie", NULL, NULL );
//	DEBUG ( window == NULL, ERROR_TYPE::WindowFail );

	glfwMakeContextCurrent ( window );
	gl3wInit ();
	init ();

	glViewport ( 0, 0, screen_width, screen_height );
	glfwSetFramebufferSizeCallback ( window, framebufferSizeCallback );

	while ( !glfwWindowShouldClose ( window ) )
	{
		processInput (window);
		display ();
		glfwSwapBuffers ( window );
		glfwPollEvents ();
	}

	glfwDestroyWindow ( window );
	glfwTerminate ();

	return EXIT_SUCCESS;
}


void
framebufferSizeCallback ( GLFWwindow *window, int width, int height )
{
	glViewport ( ZERO, ZERO, width, height );
}

void
processInput ( GLFWwindow *window )
{
	if ( glfwGetKey ( window, GLFW_KEY_ESCAPE ) )
	{
		glfwSetWindowShouldClose ( window, TRUE );
	}
}