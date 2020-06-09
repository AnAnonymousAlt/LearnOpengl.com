#include <glad/glad.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{
	glViewport ( 0, 0, width, height );

}


int
main ( int argc, char **argv )
{
	glfwInit ();

	//glfwWindowHint ( GLFW_VERSION_MAJOR, 3 );
	//glfwWindowHint ( GLFW_VERSION_MINOR, 3 );
	//glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	GLFWwindow *window = glfwCreateWindow (640, 480, "Window", NULL, NULL);
	if ( window == NULL )
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate ();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent ( window );

	if ( !gladLoadGLLoader ( ( GLADloadproc ) glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate ();
		return EXIT_FAILURE;
	}
	glViewport ( 0, 0, 640, 480 );
	glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );




}