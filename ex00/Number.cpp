#include <string>
#include <iostream>
#include "Number.hpp"

Number::Number( void ) : str( "0" )
{
	return ;
}


Number::Number( std::string const & str ) : str( str )
{
	return ;
}


Number::Number( Number const & src ) : str( src.str )
{
	return ;
}


Number::~Number( void )
{
	return ;
}


Number &			Number::operator=( Number & operand )
{
	(void)operand;

	return *this;
}


std::string const &		Number::getStr( void ) const
{
	return this->str;
}


char					Number::toChar( void ) const
{
	char				value = static_cast< char >( this->toInt() );

	return value;
}


int						Number::toInt( void ) const
{
	int					value = static_cast< int >( this->toDouble() );

	return value;
}


double					Number::toDouble( void ) const
{
	double				value = std::strtod( this->getStr().c_str(), NULL );

	return value;
}


float					Number::toFloat( void ) const
{
	float				value = static_cast< float >( this->toDouble() );

	return value;
}


std::ostream &		operator<<( std::ostream & out, Number const & operand )
{
	try
	{
		if( regex float )
		{
			convert etc.
			catch impossible
			throw
		}
		if ( regex double )
		{
			convert etc.
			catch impossible
			throw
		}
		if( regex int )
		{
			convert etc.
			catch impossible
			throw
		}
		if( char )
		{
			convert etc.
			catch impossible
			throw
		}
		not type ...
	}
/*	try
	{
		out << "char : " << operand.toChar() << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		out << "impossible" << std::endl;
	}

	try
	{
		out << "int : " << operand.toInt() << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		out << "impossible" << std::endl;
	}

	try
	{
		out << "float : " << operand.toFloat() << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		out << "nanf" << std::endl;
	}

	try
	{
		out << "double : " << operand.toDouble() << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		out << "nan" << std::endl;
	}
*/
	return out;
}
