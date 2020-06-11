#include "../include/Helper_functions.h"

void mf ()
{
	// Debugger::print ( "", ERROR_TYPE::Nullptr, __FUNCTION__, __FILE__ );
	perr ( "info", ERROR_TYPE::Nullptr );
	exit ( EXIT_FAILURE );
}
int main ( int argc, char **argv )
{
	mf ();

	// perr ( "info", ERROR_TYPE::Nullptr );

	return EXIT_SUCCESS;
}