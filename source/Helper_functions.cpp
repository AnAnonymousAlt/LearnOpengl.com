#include "Helper_functions.h"


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


std::string Debugger::errorTypeTranslater ( ERROR_TYPE error )
{
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
	default:
		break;
	}
}