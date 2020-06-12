#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

enum VAO_ID
{
	Triangle, numVAOs
};

enum BUFFER_ID
{
	ArrayBuffer, numBuffers
};

enum ATTRIB_ID
{
	vPosition
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];


void 
init ()
{
	GLfloat triangle[3][2] =
	{
		{ -0.5, -0.5 }, 
		{  0.5, -0.5 },
		{ -0.5,  0.5 }
	};

	GLuint program = glCreateProgram ();
	GLuint vShader = glCreateShader ( GL_VERTEX_SHADER );
	GLuint fShader = glCreateShader ( GL_FRAGMENT_SHADER );
	


	glClearColor ( 0.0f, 0.0f, 0.2f, 1.0f );
}

void
display ()
{
	glClear (GL_COLOR_BUFFER_BIT);
}

int
main ( int argc, char **argv )
{
	glfwInit ();
	
	GLFWwindow *window = glfwCreateWindow ( 640, 480, "Hello Triangle", NULL, NULL );
	glfwMakeContextCurrent ( window );

	gl3wInit ();
	init ();

	while ( !glfwWindowShouldClose ( window ) )
	{
		display ();
		glfwSwapBuffers ( window );
		glfwPollEvents ();
	}
	glfwDestroyWindow ( window );

	glfwTerminate ();
	return 0;
}