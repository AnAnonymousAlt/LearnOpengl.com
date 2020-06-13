#include "../include/Helper_functions.h"

enum VAO_ID
{
	H, numVAOs
};

enum BUFFER_ID
{
	ArrayBuffer, ElementBuffer, numBuffers
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
	Model mo = Helper::vertexLoader ( "H.vi" );
	Helper::elementLoader ( &mo, "H.ei" );
	Matrix maH = mo.matrixes[H];

	GLuint program = glCreateProgram ();
	GLuint vShader = glCreateShader ( GL_VERTEX_SHADER );
	GLuint fShader = glCreateShader ( GL_FRAGMENT_SHADER );
	Helper::shaderloader ( vShader, "vertex.glsl" );
	Helper::shaderloader ( fShader, "fragment.glsl" );

	glAttachShader ( program, vShader );
	glAttachShader ( program, fShader );
	glLinkProgram ( program );
	glUseProgram ( program );


	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );

	glBindVertexArray ( VAOs[H] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );
	glNamedBufferStorage ( buffers[ArrayBuffer],
						   Helper::typeSize ( GL_FLOAT_VEC4 ) * maH.vSize (),
						   maH.getVAddress (), GL_DYNAMIC_STORAGE_BIT );
	
	glVertexAttribPointer ( vPosition, VEC_SIZE::VEC4, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ), bufferOffset ( 0 ));
	glEnableVertexAttribArray ( vPosition );



	glClearColor ( 0.1f, 0.0f, 0.1f, 1.0f );
}

void
display ()
{
	glClear (GL_COLOR_BUFFER_BIT);

	glBindVertexArray ( VAOs[H] );
	glDrawArrays ( GL_TRIANGLES, 0, 4 );

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