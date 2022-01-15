#include <iostream>


typedef struct 		Data_s
{
	char			c;
	int				i;
	float			f;
	double			d;
}					Data;


uintptr_t			serialize( Data *ptr )
{
	return( reinterpret_cast< uintptr_t >( ptr ) );
}


Data				*deserialize( uintptr_t raw )
{
	return( reinterpret_cast< Data * >( raw ) );
}


int					main( void )
{
	Data			dataStart = { .c = 'a', .i = 42, .f = 4.2f, .d = 42.42 };
	std::cout << "Start pointer : " << &dataStart << std::endl;

	uintptr_t		raw = serialize( &dataStart );
	std::cout << "Int : " << raw << std::endl;

	Data			*dataEnd = deserialize( raw );
	std::cout << "End pointer : " << dataEnd << std::endl;

	return 0;
}
