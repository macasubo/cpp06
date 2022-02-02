#include <string>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <limits>
#include <math.h>
#include <stdlib.h>
#include "Number.hpp"


const char	*Number::ImpossibleException::what() const throw()
{
	return "impossible";
}


const char	*Number::NonDisplayableException::what() const throw()
{
	return "Non displayable";
}


Number::Number( void ) : _str( "0" )
{
	this->acquire();
}

Number::Number( std::string const & str ) : _str( str )
{
	this->acquire();
}

Number::Number( Number const & src ) : _str( src._str )
{
	this->acquire();
}

Number::~Number( void ) {}


Number &			Number::operator=( Number & operand )
{
	static_cast< void >( operand );

	return *this;
}


std::string const &		Number::getStr( void ) const
{
	return _str;
}


void					Number::toChar( void ) const
{
	char 				a;

	try
	{
		switch( _type )
		{
			case CHAR:
				if( !( static_cast<int>( _charN ) >= 32 && static_cast<int>( _charN ) <= 126 ) )
					throw Number::NonDisplayableException();
				a = _charN;
				break;
			case INT:
				if( !( _intN >= 32 && _intN <= 126 ) )
				{
					if( _intN >= 0 && _intN <= 127 )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( _intN );
				break;
			case FLOAT:
				if( !( _floatN >= 32.0f && _floatN <= 126.0f ) )
				{
					if( _floatN >= 0.0f && _floatN <= 127.0f )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( _floatN );
				break;
			case DOUBLE:
				if( !( _doubleN >= 32.0 && _doubleN <= 126.0 ) )
				{
					if( _doubleN >= 0.0 && _doubleN <= 127.0 )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( _doubleN );
				break;
			default:
				throw Number::ImpossibleException();
				break;
		}
		std::cout << "char: '" << a << "'" << std::endl;
	}
	catch( std::exception & e )
	{
		std::cout << "char: " << e.what() << std::endl;
	}

	return ;
}


void					Number::toInt( void ) const
{
	int					x;

	try
	{
		switch( _type )
		{
			case FLOAT:
				if( _floatN < static_cast< float >( std::numeric_limits<int>::min() )
					|| _floatN > static_cast< float >( std::numeric_limits<int>::max() )
					|| isnan( _floatN ) || isinf( _floatN ) )
					throw Number::ImpossibleException();
				x = static_cast< int >( _floatN );
				break;
			case DOUBLE:
				if( _doubleN < static_cast< double >( std::numeric_limits<int>::min() )
					|| _doubleN > static_cast< double >( std::numeric_limits<int>::max() )
					|| isnan( _doubleN ) || isinf( _doubleN ) )
					throw Number::ImpossibleException();
				x = static_cast< int >( _doubleN );
				break;
			case INT:
				x = _intN;
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "int: " << x << std::endl;
	}
	catch( std::exception & e )
	{
		std::cout << "int: " << e.what() << std::endl;
	}

	return ;
}


void					Number::toFloat( void ) const
{
	float				x;

	try
	{
		switch( _type )
		{
			case FLOAT:
				x = _floatN;
				break;
			case INT:
				x = static_cast< float >( _intN );
				break;
			case DOUBLE:
				if( _doubleN < -(static_cast< double >( std::numeric_limits<float>::max()))
				|| _doubleN > static_cast< double >( std::numeric_limits<float>::max() ) )
				{
					if( !isinf( _doubleN ) )
						throw Number::ImpossibleException();
				}
				x = static_cast< float >( _doubleN );
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "float: " << std::fixed << std::setprecision( 1 ) <<  x << "f" << std::endl;
	}
	catch( std::exception & e )
	{
		std::cout << "float: " << e.what() << std::endl;
	}

	return ;
}


void					Number::toDouble( void ) const
{
	double				x;

	try
	{
		switch( _type )
		{
			case INT:
				x = static_cast< double >( _intN );
				break;
			case FLOAT:
				x = static_cast< double >( _floatN );
				break;
			case DOUBLE:
				x = _doubleN;
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "double: " << std::fixed << std::setprecision( 1 ) << x << std::endl;
	}
	catch( std::exception & e )
	{
		std::cout << "double: " << e.what() << std::endl;
	}

	return ;
}

e_type					Number::findType( void )
{
	const char			*str = _str.c_str();
	size_t				index = 0;

	if( _str.compare( "-inff" ) == 0 || _str.compare( "+inff" ) == 0 || _str.compare( "nanf" ) == 0 )
		return FLOAT;
	if( _str.compare( "-inf" ) == 0 || _str.compare( "+inf" ) == 0 || _str.compare( "nan" ) == 0 )
		return DOUBLE;

	if( !str || !str[index] )
		return NONE;

	if( str[index] == '-' || str[index] == '+' )
		index++;

	if( !isdigit( str[index] ) )
		return NONE;
	while( isdigit( str[index] ) )
		index++;

	if( !( str[index] == '.' ) )
		return INT;
	index++;

	if( !isdigit( str[index] ) )
		return INT;
	while( isdigit( str[index] ) )
		index++;

	if( str[index] == 'f' )
		return FLOAT;
	else
		return DOUBLE;
		
}

void					Number::acquire( void )
{

	e_type		type = this->findType();
	size_t		length = _str.length();

	switch (type)
	{
		case FLOAT:
			_floatN = strtof( this->getStr().c_str(), NULL );
			if( length > 5 && _floatN > -2.0f && _floatN < 2.0f )
				_type = NONE;
			else
				_type = FLOAT;
			break;
		case DOUBLE:
			_doubleN = strtod( this->getStr().c_str(), NULL );
			if( length > 5 && _doubleN > -2.0 && _doubleN < 2.0 )
				_type = NONE;
			else
				_type = DOUBLE;
			break;
		case INT:
			long int n = strtol( this->getStr().c_str(), NULL );
			if(( length > 5 && n > -2 && n < 2 )
				|| ( n < static_cast< long int >( std::numeric_limits<int>::min() )
				|| n > static_cast< long int >( std::numeric_limits<int>::max() )))
				type = NONE;
			else
			{
				_intN = static_cast< int >( n );
				_type = INT;
			}
			break;
		default:
			if( _str.length() == 1 )
			{
				_charN = this->getStr().c_str()[0];
				_type = CHAR;
			}
			else
				type = NONE;
	}

	return;

}


void					Number::convert( void ) const
{
	this->toChar();
	this->toInt();
	this->toFloat();
	this->toDouble();
}
