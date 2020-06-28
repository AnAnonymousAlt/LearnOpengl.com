#include "../include/Helper_functions.h"

enum VAO_ID
{
	Triangle, numVAOs
};

enum Buffer_ID
{
	ABuffer0, EBuffer0, numBuffers
};

enum Program_ID
{
	Program0, numPrograms
};

enum Shader_ID
{
	VShader0, FShader0, numShaders
};

enum Attribute_ID
{
	AvPosition, numAttributes
};

enum Uniform_Loc
{
	Ucolor, numUniforms
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];
GLuint programs[numPrograms];
GLuint shaders[numShaders];

GLint uniforms[numUniforms];


Model mo;

int scr_width = 640;
int scr_height = 480;

void
framebufferSizeCallback ( GLFWwindow *window, int width, int height );

void
init ()
{
	glViewport ( 0, 0, scr_width, scr_height );

	glClearColorfv ( Color::navy );

	programs[Program0] = glCreateProgram ();
	shaders[VShader0] = glCreateShader ( GL_VERTEX_SHADER );
	Helper::shaderLoader ( shaders[VShader0], "vertex.glsl" );
	Helper::shaderCompiler ( shaders[VShader0] );
	Helper::shaderAttacher ( programs[Program0], shaders[VShader0] );

	shaders[FShader0] = glCreateShader ( GL_FRAGMENT_SHADER );
	Helper::shaderWorker ( programs[Program0], shaders[FShader0], "fragment.glsl" );
	glLinkProgram ( programs[Program0] );
	glUseProgram ( programs[Program0] );

	uniforms[Ucolor] = glGetUniformLocation ( programs[Program0], "color" );
	glUniform4f ( uniforms[Ucolor], 1.0f, 1.0f, 0.0f, 0.0f );

	glUseProgram ( ClearBit );

	mo = Helper::vertexLoader ( "VertexInfo.vi" );
	Helper::elementLoader ( &mo, "ElementInfo.ei" );

	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );

	glBindVertexArray ( VAOs[Triangle] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[ABuffer0] );
	glNamedBufferStorage ( buffers[ABuffer0],
						   Helper::typeSize ( GL_FLOAT_VEC4 ) * mo.matrixes[Triangle].vSize (),
						   mo.matrixes[Triangle].getVAddress (), GL_DYNAMIC_STORAGE_BIT );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffers[EBuffer0] );
	glNamedBufferStorage ( buffers[EBuffer0],
						   Helper::typeSize ( GL_UNSIGNED_INT_VEC3 ) * mo.matrixes[Triangle].eSize (),
						   mo.matrixes[Triangle].getEAddress (),
						   GL_DYNAMIC_STORAGE_BIT );

	glVertexAttribPointer ( AvPosition, VEC_SIZE::VEC4, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC4 ), bufferOffset ( 0 ) );
	glEnableVertexAttribArray ( AvPosition );

	glBindVertexArray ( ClearBit );
	glBindBuffer ( GL_ARRAY_BUFFER, ClearBit );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ClearBit );
	glDeleteShader ( shaders[VShader0] );
	glDeleteShader ( shaders[FShader0] );

}

void
display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );

	glUseProgram ( programs[Program0] );

	glBindVertexArray ( VAOs[Triangle] );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	
	glUniformRGBA ( uniforms[Ucolor], Color::red );
	glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
	glUniformRGBA ( uniforms[Ucolor], Color::yellow );


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
	glfwSetFramebufferSizeCallback ( window, framebufferSizeCallback );

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

void framebufferSizeCallback ( GLFWwindow *window, int width, int height )
{
	glViewport ( 0, 0, width, height );

}