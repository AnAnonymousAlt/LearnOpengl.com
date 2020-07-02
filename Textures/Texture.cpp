#include "../include/Helper_functions.h"
#include <stb/stb_image.h>

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
	AvPosition, AvColor, AvTexCoord, numAttrib
};

enum Uniform_ID
{
	Ucrimson, UsContainer, UsFace, numUniforms
};

enum Texture_ID
{
	Tcontainer, Tface, numTextures
};

GLuint VAOs[numVAOs];
GLuint buffers[numBuffers];
GLuint programs[numPrograms];
GLuint shaders[numShaders];
GLuint textures[numTextures];
GLint uniforms[numUniforms];

Model mo;

void
init ()
{
	GLfloat vArray[] =
	{
		// positions    // color            // texture coords
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top left
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // bot left
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bot right
		 0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f  // top right
	};

	GLuint eArray[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	GLint width, height, nrChannels;
	GLubyte *textureData0, *textureData1;

	glClearColorfv ( Color::grey );


	glCreateVertexArrays ( numVAOs, VAOs );
	glCreateBuffers ( numBuffers, buffers );
	glGenTextures ( numTextures, textures );

	programs[Program0] = glCreateProgram ();
	shaders[VShader0] = glCreateShader ( GL_VERTEX_SHADER );
	shaders[FShader0] = glCreateShader ( GL_FRAGMENT_SHADER );

	Helper::shaderWorker ( programs[Program0], shaders[VShader0],
						   "Vertex.glsl" );
	Helper::shaderWorker ( programs[Program0], shaders[FShader0],
						   "Fragment.glsl" );
	glLinkProgram ( programs[Program0] );
	uniforms[Ucrimson] = glGetUniformLocation ( programs[Program0],
												"crimson" );
	uniforms[UsContainer] = glGetUniformLocation ( programs[Program0], 
												   "sContainer" );
	uniforms[UsFace] = glGetUniformLocation ( programs[Program0],
											  "sFace" );

	glBindVertexArray ( VAOs[Triangle] );
	glBindBuffer ( GL_ARRAY_BUFFER, buffers[Abuffer0] );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, buffers[Ebuffer0] );
	glNamedBufferStorage ( buffers[Abuffer0],
						   sizeof ( vArray ),
						   vArray,
						   GL_DYNAMIC_STORAGE_BIT );
	glVertexAttribPointer ( AvPosition, VEC_SIZE::VEC2,
							GL_FLOAT, GL_FALSE,
							( 2 + 3 + 2 ) * Helper::typeSize ( GL_FLOAT ),
							bufferOffset ( ZERO ) );
	glEnableVertexAttribArray ( AvPosition );
	glVertexAttribPointer ( AvColor, VEC_SIZE::VEC3, GL_FLOAT, GL_FALSE,
							( 2 + 3 + 2 ) * Helper::typeSize ( GL_FLOAT ),
							bufferOffset ( 2 * Helper::typeSize ( GL_FLOAT ) ) );
	glEnableVertexAttribArray ( AvColor );
	glVertexAttribPointer ( AvTexCoord, VEC_SIZE::VEC2, GL_FLOAT, GL_FALSE,
							( 2 + 3 + 2 ) * Helper::typeSize ( GL_FLOAT ),
							bufferOffset ( ( 2 + 3 ) * Helper::typeSize ( GL_FLOAT ) ) );
	glEnableVertexAttribArray ( AvTexCoord );

	glUseProgram ( programs[Program0] );
	glActiveTexture ( GL_TEXTURE0 );
	glBindTexture ( GL_TEXTURE_2D, textures[Tcontainer] );
	glUniform1i ( uniforms[UsContainer], 0 );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	textureData0 = stbi_load ( "container.jpg", &width, &height,
							  &nrChannels, 0 );
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				   GL_UNSIGNED_BYTE, textureData0 );
	glGenerateMipmap ( GL_TEXTURE_2D );
	stbi_image_free ( textureData0 );

	glActiveTexture ( GL_TEXTURE1 );
	glBindTexture ( GL_TEXTURE_2D, textures[Tface] );
	glUniform1i ( uniforms[UsFace], 1 );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	stbi_set_flip_vertically_on_load ( true );
	textureData1 = stbi_load ( "face.png", &width, &height,
							  &nrChannels, 0 );
	if ( !textureData1 )
	{
		std::cout << "error face" << std::endl;
	}
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
				   GL_UNSIGNED_BYTE, textureData1 );
	glGenerateMipmap ( GL_TEXTURE_2D );
	stbi_image_free ( textureData1 );


	glUseProgram ( ClearBit );

	glNamedBufferStorage ( buffers[Ebuffer0],
						   sizeof ( eArray ),
						   eArray,
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
	glUniformRGBA ( uniforms[Ucrimson], Color::crimson );
	glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
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
	glViewport ( 0, 0, width, height );
}
