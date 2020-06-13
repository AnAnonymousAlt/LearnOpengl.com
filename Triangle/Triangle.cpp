#include "../include/Helper_functions.h"


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


void init ()
{
	std::vector<glm::vec4> *matrixes = NULL;
	Helper::vertexLoader ( matrixes, "Triangle.vi" );


	// Load shader
	GLuint program = glCreateProgram ();
	GLuint vShader = glCreateShader ( GL_VERTEX_SHADER );
	GLuint fShader = glCreateShader ( GL_FRAGMENT_SHADER );
	Helper::shaderloader ( vShader, "vertex.glsl" );
	Helper::shaderloader ( fShader, "fragment.glsl" );

	glAttachShader ( program, vShader );
	glAttachShader ( program, fShader );
	glLinkProgram ( program );
	glUseProgram ( program );

	// Load Shader ends

	//// load VAO
	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );

	glBindVertexArray ( VAOs[Triangle] );

	glBindBuffer ( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );

	/*glNamedBufferStorage ( buffers[ArrayBuffer], sizeof ( ), 
						   &(matrixes[0]), GL_DYNAMIC_STORAGE_BIT );*/
	glVertexAttribPointer ( vPosition, numElement, GL_FLOAT, GL_FALSE, 
							Helper::typeSize(GL_FLOAT_VEC2), bufferOffset(0));
	glEnableVertexAttribArray ( vPosition );
	// load VAO ends

	// Set GL variable
	glClearColor ( 0.0f, 0.1f, 0.3f, 1.0f );

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

	glViewport ( 0, 0, 640, 480 );
	glfwSetFramebufferSizeCallback ( window, frameBufferSizeCallback );

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