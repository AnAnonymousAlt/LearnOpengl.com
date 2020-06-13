#include "../include/Helper_functions.h"


void Helper::print ( const char *info, ERROR_TYPE error,
					 const char *funcName, int line, const char *fileName )
{
	std::cerr
		<< "ERROR: \""						// ERROR: "
		<< info								// INFO
		<< "\", \n\nCODE: \""					// ", CODE: "
		<< errorTranslater ( error )	// error type
		<< " "								// 
		<< ( int ) error					// error_code
		<< "\", at function: \""			// ", at function: "
		<< funcName							// function name
		<< "\", \nin file: \""				// ", in file "
		<< fileName							// filename
		<< "\" line: "						// " line: 
		<< line								// line number
		<< std::endl;
}

void Helper::print ( char *info, ERROR_TYPE error,
					 const char *funcName, int line, const char *fileName )
{
	std::cerr
		<< "ERROR: \""						// ERROR: "
		<< info								// INFO
		<< "\", \n\nCODE: \""					// ", CODE: "
		<< errorTranslater ( error )	// error type
		<< " "								// 
		<< ( int ) error					// error_code
		<< "\", at function: \""			// ", at function: "
		<< funcName							// function name
		<< "\", \nin file: \""				// ", in file "
		<< fileName							// filename
		<< "\" line: "						// " line: 
		<< line								// line number
		<< std::endl;
}

std::string Helper::errorTranslater ( ERROR_TYPE error )
{
	#define CASE(Enum, code) \
	case Enum: \
		return std::string(code); \
		break

	switch ( error )
	{
		CASE ( ERROR_TYPE::EmptyString, "EmptyString" );
		CASE ( ERROR_TYPE::NullPtr, "NullPtr" );
		CASE ( ERROR_TYPE::LinkError, "LinkError" );
		CASE ( ERROR_TYPE::CompileError, "CompileError" );
		CASE ( ERROR_TYPE::FileNotExit, "FileNotExit" );
		CASE ( ERROR_TYPE::InvalidShader, "InvalidShader" );
		CASE ( ERROR_TYPE::EmptyMatrixVertex, "EmptyMatrixVertex" );
		#undef CASE
	default:
		return std::string ( "UndefinedERROR" );
	}
}


std::string Helper::fileLoader ( const char *filename, GLint *length )
{
	DEBUG ( length == NULL, ERROR_TYPE::NullPtr );
	DEBUG ( filename == NULL, ERROR_TYPE::NullPtr );

	std::ifstream fs ( filename );

	DEBUG ( !fs.is_open (), ERROR_TYPE::FileNotExit );

	std::string s = std::string ( std::istreambuf_iterator<char> ( fs ), std::istreambuf_iterator<char> () );

	DEBUG ( s.empty (), ERROR_TYPE::EmptyString );

	*length = ( GLint ) s.length ();
	s = s;
	return s;
}



void Helper::shaderloader ( GLuint shader, const char *filename )
{
	DEBUG ( !glIsShader ( shader ), ERROR_TYPE::InvalidShader );
	DEBUG ( filename == "", ERROR_TYPE::EmptyString );

	GLint length;
	const char *text;
	std::string s = fileLoader ( filename, &length ).c_str ();

	DEBUG ( s.empty (), ERROR_TYPE::FileNotExit );

	text = s.c_str ();
	glShaderSource ( shader, 1, &text, &length );
	glCompileShader ( shader );

	GLint status;
	glGetShaderiv ( shader, GL_COMPILE_STATUS, &status );
	if ( !status )
	{
		char *errorLog = ( char * ) malloc ( ( size_t ) 512 );
		glGetShaderInfoLog ( shader, ( GLsizei ) 512, NULL, errorLog );

		DEBUGP ( errorLog, ERROR_TYPE::CompileError );
	}
}

Model Helper::vertexLoader ( const char *filename )
{
	GLint length, numMatrixes, numVertices, numElements;
	Model mo;
	
	std::string s = fileLoader (filename, &length);
	std::istringstream iss ( s, std::ios_base::in );
	std::string ModelName;

	// Get number of matrixes and filename
	iss >> numMatrixes >> ModelName;

	// read matrixes
	for ( int matrix_num = 0; matrix_num < numMatrixes; matrix_num++ )
	{
		Matrix ma;
		std::string matrixName;

		iss >> numVertices >> numElements >> matrixName;
		ma.addName ( matrixName );
		
		// read vertices
		for ( int vertex_num = 0; vertex_num < numVertices; vertex_num++ )
		{
			std::vector<GLfloat> vertex_;
			
			// Read element
			for ( int element_num = 0; element_num < numElements; element_num++ )
			{
				GLfloat element;
				iss >> element;
				vertex_.push_back ( element );

			}
			if ( numElements == 2 )
			{
				vertex_.push_back ( 0.0f );
				vertex_.push_back ( 1.0f );
			}
			else if ( numElements == 3 )
			{
				vertex_.push_back ( 1.0f );
			}
			glm::vec4 vertex ( vertex_[0], vertex_[1], vertex_[2], vertex_[3] );
			ma.addVertex ( vertex );
		}

		mo.addMatrix ( ma );
		
	}
	return mo;
}


size_t
Helper::typeSize ( GLenum type )
{
	size_t size;

	#define CASE(Enum, Count, Type) \
	case Enum: size = Count * sizeof (Type); break

	switch ( type )
	{
		CASE ( GL_FLOAT, 1, GLfloat );
		CASE ( GL_FLOAT_VEC2, 2, GLfloat );
		CASE ( GL_FLOAT_VEC3, 3, GLfloat );
		CASE ( GL_FLOAT_VEC4, 4, GLfloat );
		CASE ( GL_INT, 1, GLint );
		CASE ( GL_INT_VEC2, 2, GLint );
		CASE ( GL_INT_VEC3, 3, GLint );
		CASE ( GL_INT_VEC4, 4, GLint );
		CASE ( GL_UNSIGNED_INT, 1, GLuint );
		CASE ( GL_UNSIGNED_INT_VEC2, 2, GLuint );
		CASE ( GL_UNSIGNED_INT_VEC3, 3, GLuint );
		CASE ( GL_UNSIGNED_INT_VEC4, 4, GLuint );
		CASE ( GL_BOOL, 1, GLboolean );
		CASE ( GL_BOOL_VEC2, 2, GLboolean );
		CASE ( GL_BOOL_VEC3, 3, GLboolean );
		CASE ( GL_BOOL_VEC4, 4, GLboolean );
		CASE ( GL_FLOAT_MAT2, 4, GLfloat );
		CASE ( GL_FLOAT_MAT2x3, 6, GLfloat );
		CASE ( GL_FLOAT_MAT2x4, 8, GLfloat );
		CASE ( GL_FLOAT_MAT3, 9, GLfloat );
		CASE ( GL_FLOAT_MAT3x2, 6, GLfloat );
		CASE ( GL_FLOAT_MAT3x4, 12, GLfloat );
		CASE ( GL_FLOAT_MAT4, 16, GLfloat );
		CASE ( GL_FLOAT_MAT4x2, 8, GLfloat );
		CASE ( GL_FLOAT_MAT4x3, 12, GLfloat );
		#undef CASE
	default:
		fprintf ( stderr, "Unknown type: -x%x\n", type );
		exit ( EXIT_FAILURE );
		break;
	}
	return size;
}


Model::Model ()
{

}

int Model::length ()
{
	return ( int ) this->matrixes.size ();
}

std::string Model::getName ()
{
	return this->name;
}

bool Model::addName ( std::string name )
{
	this->name = name;
	return true;
}

bool Model::addMatrix ( Matrix matrix )
{
	this->matrixes.push_back(matrix);
	return true;
}

Matrix Model::getMatrix ( int number )
{
	return this->matrixes[number];
}


std::vector< Matrix > Model::getModel ()
{
	return this->matrixes;
}


Matrix::Matrix ()
{

}


bool Matrix::addName ( std::string name )
{
	this->name = name;
	return true;
}

bool Matrix::addVertex ( glm::vec4 vertex )
{
	this->vertices.push_back ( vertex );
	return true;
}

int Matrix::length ()
{
	return (int)this->vertices.size ();
}



std::string Matrix::getName ()
{
	return this->name;
}

std::vector<glm::vec4> Matrix::getVector ()
{
	return this->vertices;
}

glm::vec4 Matrix::getVertex ( int num )
{
	return vertices[num];
}

void *Matrix::getPointer ()
{
	return &vertices[0];
}
