#include "Helper_functions.h"

void Debugger::print ( ERROR_TYPE error )
{
	std::cerr << "";
}

/// <summary>
/// 
/// </summary>
/// <param name="error"></param>
/// <returns></returns>
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