#include <string>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <regex>
#include <limits>
#include <math.h>
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
	(void)operand;

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
				if( _floatN < static_cast< float >( std::numeric_limits<int>::lowest() )
					|| _floatN > static_cast< float >( std::numeric_limits<int>::max() )
					|| isnan( _floatN ) || isinf( _floatN ) )
					throw Number::ImpossibleException();
				x = static_cast< int >( _floatN );
				break;
			case DOUBLE:
				if( _doubleN < static_cast< double >( std::numeric_limits<int>::lowest() )
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
				if( _doubleN < static_cast< double >( std::numeric_limits<float>::lowest() )
				|| _doubleN > static_cast< double >( std::numeric_limits<float>::max() ) )
					if( !isinf( _doubleN ) )
						throw Number::ImpossibleException();
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




void					Number::acquire( void )
{

	std::regex		float_regex("((\\+|-)?\\d+\\.\\d+f)|-inff|\\+inff|nanf");
	std::regex		double_regex("((\\+|-)?\\d+\\.\\d+)|-inf|\\+inf|nan");
	std::regex		int_regex("(\\+|-)?\\d+");

	if( regex_match( this->getStr(), float_regex ) )
	{
		_floatN = strtof( this->getStr().c_str(), NULL );
		_type = FLOAT;
	}
	else if( regex_match( this->getStr(), double_regex ) )
	{
		_doubleN = strtod( this->getStr().c_str(), NULL );
		_type = DOUBLE;
	}
	else if( regex_match( this->getStr(), int_regex ) )
	{
		_intN = atoi( this->getStr().c_str() );
		_type = INT;
	}
	else if( this->getStr().length() == 1 )
	{
		_charN = this->getStr().c_str()[0];
		_type = CHAR;
	}
	else
		_type = NONE;

	return;

}


void					Number::convert( void ) const
{
	this->toChar();
	this->toInt();
	this->toFloat();
	this->toDouble();
}
