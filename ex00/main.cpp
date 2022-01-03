#include <iostream>
#include <string>
#include "Number.hpp"


int			main( int argc, char **argv )
{
	if( argc < 2 )
	{
		std::cout << "One argument needed." << std::endl;
		return 0;
	}

	argv++;

	std::string	const str = *argv;

	Number	x = Number( str );

	std::cout << x;

	return 0;
}
