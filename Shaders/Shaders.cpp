#include "../include/Helper_functions.h"

int scr_width = 640;
int scr_height = 480;


void framebufferSizeFunc ( GLFWwindow *window, int width, int height );

enum VAO_ID
{
	Triangle, numVAOs
};

enum Buffer_ID
{
	Abuffer0, Ebuffer0, numBuffers
};

enum Program_ID
{
	Program0, numPrograms
};

enum Shader_ID
{
	VShader0, FShader0, numShaders
};

enum Attrib_ID
{
	vPosition, vColor, numAttrib
};

enum Uniform_ID
{
	UtimeColor, Uright, numUniforms
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];
GLuint programs[numPrograms];
GLuint shaders[numShaders];
GLint uniforms[numUniforms];

Model mo;

void
init ()
{
	GLfloat data[] =
	{
		-0.375f, -0.29f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.375f, -0.29f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		   0.0f,  0.58f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};
	glClearColorfv ( Color::grey );

	mo = Helper::vertexLoader ( "VertexInfo.vi" );
	Helper::elementLoader ( &mo, "ElementInfo.ei" );


	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );
	programs[Program0] = glCreateProgram ();
	shaders[VShader0] = glCreateShader ( GL_VERTEX_SHADER );
	shaders[FShader0] = glCreateShader ( GL_FRAGMENT_SHADER );

	Helper::shaderWorker ( programs[Program0], shaders[VShader0],
						   "Vertex.glsl" );
	Helper::shaderWorker ( programs[Program0], shaders[FShader0],
						   "Fragment.glsl" );
	glLinkProgram ( programs[Program0] );
	uniforms[UtimeColor] = glGetUniformLocation ( programs[Program0],
												  "timeColor" );
	uniforms[Uright] = glGetUniformLocation ( programs[Program0],
											  "right" );
	glBindVertexArray ( VAOs[Triangle] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[Abuffer0] );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffers[Ebuffer0] );
	glNamedBufferStorage ( buffers[Abuffer0],
						   sizeof ( data ),
						   &data,
						   GL_DYNAMIC_STORAGE_BIT );
	glVertexAttribPointer ( vPosition, VEC_SIZE::VEC4,
							GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ) * 2,
							bufferOffset ( ZERO ) );
	glVertexAttribPointer ( vColor, VEC_SIZE::VEC4,
							GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ) * 2,
							( void * ) ( Helper::typeSize ( GL_FLOAT_VEC4 ) ) );
	glEnableVertexAttribArray ( vPosition );
	glEnableVertexAttribArray ( vColor );
	glNamedBufferStorage ( buffers[Ebuffer0],
						   mo.matrixes[Triangle].eSize (),
						   mo.matrixes[Triangle].getEAddress (),
						   GL_DYNAMIC_STORAGE_BIT );
	glBindVertexArray ( ClearBit );

	glDeleteShader ( shaders[VShader0] );
	glDeleteShader ( shaders[FShader0] );
}

void
display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glBindVertexArray ( VAOs[Triangle] );
	glUseProgram ( programs[Program0] );
	glUniform1i ( uniforms[Uright], 0 );
	double ct = glfwGetTime ();
	glm::vec4 timeColor = Color::blue;
	timeColor.b = ( GLfloat ) ( sin ( ct * 3.14 ) / 2.0 + 0.5 );
	glUniformRGBA ( uniforms[UtimeColor], timeColor );
	glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
	glUniform1i ( uniforms[Uright], 1 );
	glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
	glBindVertexArray ( ClearBit );
	glUseProgram ( ClearBit );

}

int
main ( int argc, char **argv )
{
	glfwInit ();

	GLFWwindow *window = glfwCreateWindow ( scr_width, scr_height, "Review",
											NULL, NULL );

	glfwMakeContextCurrent ( window );

	gl3wInit ();
	init ();

	glfwSetFramebufferSizeCallback ( window, framebufferSizeFunc );

	while ( !glfwWindowShouldClose ( window ) )
	{
		display ();
		glfwSwapBuffers ( window );
		glfwPollEvents ();
	}
	glDeleteProgram ( programs[Program0] );
	glfwDestroyWindow ( window );
	glfwTerminate ();
	return 0;
}

void framebufferSizeFunc ( GLFWwindow *window, int width, int height )
{
	//glViewport ( 0, 0, width, height );
}
