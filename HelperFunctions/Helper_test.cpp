#include "../include/Helper_functions.h"

Model f ()
{
	Model mo;
	Matrix ma;

	glm::vec4 v = glm::vec4 ( 1.0f, 1.0f, 0.0f, 1.0f );

	mo.addMatrix ( ma );

	ma.addVertex ( v );

	mo.addMatrix ( ma );

	return mo;
}

int main ( int argc, char **argv )
{

	Model mo = Helper::vertexLoader ( "Vertex.vi" );

	return EXIT_SUCCESS;

}