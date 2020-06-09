#include "Helper_functions.h"

void mf ()
{
	Debugger::print ( "", ERROR_TYPE::Nullptr, __FUNCTION__, __FILE__ );
	exit ( EXIT_FAILURE );
}
int main ( int argc, char **argv )
{
	mf ();
	
	return EXIT_SUCCESS;
}