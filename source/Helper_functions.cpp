#include "../include/Helper_functions.h"


void Debugger::print (const char *info, ERROR_TYPE error,
					   const char *funcName, int line, const char *fileName)
{
	std::cerr
		<< "ERROR: \""						// ERROR: "
		<< info								// INFO
		<< "\", CODE: \""					// ", CODE: "
		<< errorTypeTranslater ( error )	// error type
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

void Debugger::print ( char *info, ERROR_TYPE error,
					   const char *funcName, int line, const char *fileName )
{
	std::cerr
		<< "ERROR: \""						// ERROR: "
		<< info								// INFO
		<< "\", CODE: \""					// ", CODE: "
		<< errorTypeTranslater ( error )	// error type
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

std::string Debugger::errorTypeTranslater ( ERROR_TYPE error )
{
	#define CASE(Enum, code) \
	case Enum: \
		return std::string(code); \
		break

	switch ( error )
	{
	case ERROR_TYPE::Nullptr:
		return std::string ( "Nullptr" );
		break;
	case ERROR_TYPE::LinkError:
		return std::string ( "LinkError" );
		break;
	case ERROR_TYPE::CompileError:
		return std::string ( "CompileError" );
		break;
	case ERROR_TYPE::FileNotExit:
		return std::string ( "FileNotExit" );
		break;
	case ERROR_TYPE::InvalidShader:
		return std::string ( "InvalidShader" );
		break;
	CASE ( ERROR_TYPE::EmptyString, "EmptyString" );
	default:
		return std::string ( "UndefinedERROR" );
	}
}


std::string fileloader ( const char *filename, GLint *length )
{
	if ( length == NULL )
	{
		perr ( "Length is NULL", ERROR_TYPE::Nullptr );
		exit ( EXIT_FAILURE );
	}
	if ( filename == NULL )
	{
		perr ( "filename is NULL", ERROR_TYPE::Nullptr );
		exit ( EXIT_FAILURE );
	}

	std::ifstream fs ( filename );
	if ( !fs.is_open () )
	{
		perr ( "file invalid", ERROR_TYPE::FileNotExit );
		exit ( EXIT_FAILURE );
	}
	std::string s = std::string ( std::istreambuf_iterator<char> ( fs ), std::istreambuf_iterator<char> () );
	if ( s.empty() )
	{
		perr ( "file invalid", ERROR_TYPE::FileNotExit );
		exit ( EXIT_FAILURE );
	}
	*length = ( GLint ) s.length ();
	s = s;
	return s;
}

#define DEBUG(errorCondition, code) \
if ( errorCondition ) \
{ \
	Debugger::print ( "", code, __FUNCTION__, __LINE__, __FILE__ );  \
	exit ( EXIT_FAILURE ); \
} \


void shaderloader ( GLuint shader, const char *filename )
{
	DEBUG ( !glIsShader ( shader ), ERROR_TYPE::InvalidShader );

	DEBUG ( filename == "", ERROR_TYPE::EmptyString );

	
	GLint length;
	const char *text;
	std::string s = fileloader ( filename, &length ).c_str();
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
		perr ( errorLog, ERROR_TYPE::CompileError );
		exit ( EXIT_FAILURE );
	}
	return;
}


size_t
typeSize ( GLenum type )
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
	default:
		fprintf ( stderr, "Unknown type: -x%x\n", type );
		#undef CASE
		exit ( EXIT_FAILURE );
		break;
	}
	#undef CASE
	return size;
}