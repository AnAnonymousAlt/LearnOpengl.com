#include "Helper_functions.h"


void Debugger::print (const char *info, ERROR_TYPE error, const char *funcName, const char *fileName)
{
	std::cerr
		<< "ERROR: \""
		<< info
		<< "\", CODE: \""
		<< errorTypeTranslater ( error )
		<< " "
		<< ( int ) error
		<< "\", at function: \""
		<< funcName
		<< "\", \nin file: \""
		<< fileName
		<< "\""
		<< std::endl;
}


std::string Debugger::errorTypeTranslater ( ERROR_TYPE error )
{
	switch ( error )
	{
	case ERROR_TYPE::Nullptr:
		return std::string ( "Nullptr" );
		break;
	default:
		break;
	}
}