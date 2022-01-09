#include <iostream>


typedef struct 		Data_s
{
	char			a;
	int				x;
}					Data;


static uintptr_t	serialize( Data *ptr )
{
	return( reinterpret_cast< uintptr_t >( ptr ) );
}


Data				*deserialize( uintptr_t raw )
{
	return( reinterpret_cast< Data * >( raw ) );
}


int					main( void )
{
	Data			dataStart = { .a = 'a', .x = 42 };

	uintptr_t		raw = serialize( &dataStart );
	
	std::cout << "Int : " << raw << std::endl;

	Data			*dataEnd = deserialize( raw );

	std::cout << "Start pointer : " << &dataStart << std::endl;
	std::cout << "End pointer : " << dataEnd << std::endl;

	return 0;
}
