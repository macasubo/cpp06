#include <iostream>
#include <cstdlib>
#include "Base.hpp"


Base			*generate( void )
{
	int			random = rand() % 3;

	if( random == 0 )
		return( new A() );
	if( random == 1 )
		return( new B() );
	return( new C() );
}


void			identify( Base *p )
{
	if( dynamic_cast< A * >( p ) )
		std::cout << "A" << std::endl;
	else if( dynamic_cast< B * >( p ) )
		std::cout << "B" << std::endl;
	else if( dynamic_cast< C * >( p ) )
		std::cout << "C" << std::endl;

	return ;
}


void			identify( Base &p )
{
	try
	{
		(void)dynamic_cast< A & >( p );
		std::cout << "A" << std::endl;
		return ;
	}
	catch( std::bad_cast & bc ) {}

	try
	{
		(void)dynamic_cast< B & >( p );
		std::cout << "B" << std::endl;
		return ;
	}
	catch( std::bad_cast & bc ) {}

	try
	{
		(void)dynamic_cast< C & >( p );
		std::cout << "C" << std::endl;
		return ;
	}
	catch( std::bad_cast & bc ) {}
}


int				main( void )
{
	srand( time( 0 ) );

	Base		*instance = generate();

	identify( instance );
	identify( *instance );

	delete instance;

	return 0;
}
