#include "../include/Helper_functions.h"
#include <stb/stb_image.h>

void framebufferSizeFunc ( GLFWwindow *window, int width, int height );

const int scr_width = 800;
const int scr_height = 800;

enum VAO_ID
{
	Box, numVAOs
};

enum Buffer_ID
{
	AbBox, numBuffers
};

enum Attrib_ID
{
	AvPos = 0, AvTexCoord = 1
};

enum Uniform_id
{
	UsContainer, numUniforms
};

enum Texture_ID
{
	TContainer, numTextures
};

enum Program_ID
{
	PBox, numPrograms
};

enum Shader_ID
{
	VBox, FBox, numShaders,
};

GLuint vaos[numVAOs];
GLuint bfrs[numBuffers];
GLuint pgms[numPrograms];
GLuint sdrs[numShaders];
GLuint unfs[numUniforms];
GLuint texs[numTextures];

void
init ()
{
	// Initialize Global gl variables
	glClearColorfv ( Color::grey );
	glViewport ( ZERO, ZERO, scr_width, scr_height );

	// Varaibles Creation
	GLfloat vArray[] =
	{
		-0.5, -0.5,  0.0,  0.0,  0.0,
		-0.5,  0.5,  0.0,  0.0,  1.0,
		 0.5,  0.5,  0.0,  1.0,  1.0,
		 0.5,  0.5,  0.0,  1.0,  1.0,
		 0.5, -0.5,  0.0,  1.0,  0.0,
		-0.5, -0.5,  0.0,  0.0,  0.0
	};
	GLubyte *texData;
	GLint width, height, nrChannels;
	glCreateVertexArrays ( numVAOs, vaos );
	glCreateBuffers ( numBuffers, bfrs );
	glCreateTextures ( GL_TEXTURE_2D, numTextures, texs );
	pgms[PBox] = glCreateProgram ();
	sdrs[VBox] = glCreateShader ( GL_VERTEX_SHADER );
	sdrs[FBox] = glCreateShader ( GL_FRAGMENT_SHADER );

	// Programs
	Helper::shaderWorker ( pgms[PBox], sdrs[VBox], "vertex.glsl" );
	Helper::shaderWorker ( pgms[PBox], sdrs[FBox], "fragment.glsl" );
	glLinkProgram ( pgms[PBox] );
	glDeleteShader ( sdrs[VBox] );
	glDeleteShader ( sdrs[FBox] );

	// VAOs
	glBindVertexArray ( vaos[Box] );
	glBindBuffer ( GL_ARRAY_BUFFER, bfrs[AbBox] );
	glNamedBufferStorage ( bfrs[AbBox], sizeof ( vArray ), vArray,
						   GL_DYNAMIC_STORAGE_BIT );
	glVertexAttribPointer ( AvPos, VEC_SIZE::VEC3, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC3 )
							+ Helper::typeSize ( GL_FLOAT_VEC2 ),
							bufferOffset ( 0 ) );
	glEnableVertexAttribArray ( AvPos );
	glVertexAttribPointer ( AvTexCoord, VEC_SIZE::VEC2, GL_FLOAT, GL_FALSE,
							Helper::typeSize ( GL_FLOAT_VEC3 )
							+ Helper::typeSize ( GL_FLOAT_VEC2 ),
							bufferOffset ( Helper::typeSize ( GL_FLOAT_VEC3 ) ) );
	glEnableVertexAttribArray ( AvTexCoord );
	glBindVertexArray ( ClearBit );
	glBindBuffer ( GL_ARRAY_BUFFER, ClearBit );

	// Uniforms
	unfs[UsContainer] = glGetUniformLocation ( pgms[PBox], "sContainer" );

	// Textures
	glActiveTexture ( GL_TEXTURE0 );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					  GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture ( GL_TEXTURE_2D, texs[TContainer] );
	glUseProgram ( pgms[PBox] );
	glUniform1i ( unfs[UsContainer], TContainer );
	glUseProgram ( ClearBit );
	texData = stbi_load ( "container.jpg", &width, &height, &nrChannels, 0 );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				   GL_UNSIGNED_BYTE, texData );
	glGenerateMipmap ( GL_TEXTURE_2D );
	stbi_image_free ( texData );
}

void
display ()
{
	glClear ( GL_COLOR_BUFFER_BIT );
	glUseProgram ( pgms[PBox] );
	glBindVertexArray ( vaos[Box] );
	glDrawArrays ( GL_TRIANGLES, 0, 6 );
	glBindVertexArray ( ClearBit );

}

void
terminate ()
{
	glDeleteProgram ( pgms[PBox] );
}

int
main ( int argc, char **argv )
{
	glfwInit ();
	GLFWwindow *window = glfwCreateWindow ( scr_width, scr_height,
											"Coordinate System",
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
	terminate ();
	glfwDestroyWindow ( window );
	glfwTerminate ();
	return EXIT_SUCCESS;
}

void
framebufferSizeFunc ( GLFWwindow *window, int width, int height )
{
	glViewport ( 0, 0, width, height );
}