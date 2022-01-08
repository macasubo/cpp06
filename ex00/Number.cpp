#include <string>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <regex>
#include <limits>
#include <math.h>
#include "Number.hpp"

Number::Number( void ) : str( "0" )
{
	this->convert();

	return ;
}


Number::Number( std::string const & str ) : str( str )
{
	this->convert();

	return ;
}


Number::Number( Number const & src ) : str( src.str )
{
	this->convert();

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


void					Number::toChar( void ) const
{
	char 				a;

	try
	{
		switch( this->type )
		{
			case INT:
				if( !( this->intN >= 32 && this->intN <= 126 ) )
				{
					if ( this->intN >= 0 && this->intN <= 127 )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( this->intN );
				break;
			case FLOAT:
				if( !( this->floatN >= 32 && this->floatN <= 126 ) )
				{
					if( this->floatN >= 0 && this->floatN <= 127 )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( this->floatN );
				break;
			case DOUBLE:
				if( !( this->doubleN >= 32 && this->doubleN <= 126) )
				{
					if( this->doubleN >= 0 && this->doubleN <= 127 )
						throw Number::NonDisplayableException();
					throw Number::ImpossibleException();
				}
				a = static_cast< char >( this->doubleN );
				break;
			default:
				throw Number::ImpossibleException();
				break;
		}
		std::cout << "char: '" << a << "'" << std::endl;
	}
	catch( Number::NonDisplayableException & e )
	{
		std::cout << "char: Non displayable" << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		std::cout << "char: impossible" << std::endl;
	}

	return ;
}


void					Number::toInt( void ) const
{
	int					x;

	try
	{
		switch( this->type )
		{
			case FLOAT:
				if( this->floatN < static_cast< float >( std::numeric_limits<int>::lowest() )
					|| this->floatN > static_cast< float >( std::numeric_limits<int>::max() )
					|| isnan( this->floatN ) || isinf( this->floatN ) )
					throw Number::ImpossibleException();
				x = static_cast< int >( this->floatN );
				break;
			case DOUBLE:
				if( this->doubleN < static_cast< double >( std::numeric_limits<int>::lowest() )
					|| this->doubleN > static_cast< double >( std::numeric_limits<int>::max() )
					|| isnan( this->doubleN ) || isinf( this->doubleN ) )
					throw Number::ImpossibleException();
				x = static_cast< int >( this->doubleN );
				break;
			case INT:
				x = this->intN;
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "int: " << x << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		std::cout << "int: impossible" << std::endl;
	}

	return ;
}


void					Number::toFloat( void ) const
{
	float				x;

	try
	{
		switch( this->type )
		{
			case FLOAT:
				x = this->floatN;
				break;
			case INT:
				x = static_cast< float >( this->intN );
				break;
			case DOUBLE:
				if( this->doubleN < static_cast< double >( std::numeric_limits<float>::lowest() )
				|| this->doubleN > static_cast< double >( std::numeric_limits<float>::max() ) )
					if( !isinf( this->doubleN ) )
						throw Number::ImpossibleException();
				x = static_cast< float >( this->doubleN );
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "float: " << std::fixed << std::setprecision( 1 ) <<  x << "f" << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		std::cout << "float: impossible" << std::endl;
	}

	return ;
}


void					Number::toDouble( void ) const
{
	double				x;

	try
	{
		switch( this->type )
		{
			case INT:
				x = static_cast< double >( this->intN );
				break;
			case FLOAT:
				x = static_cast< double >( this->floatN );
				break;
			case DOUBLE:
				x = this->doubleN;
				break;
			default:
				throw Number::ImpossibleException();
		}
		std::cout << "double: " << std::fixed << std::setprecision( 1 ) << x << std::endl;
	}
	catch( Number::ImpossibleException & e )
	{
		std::cout << "double: impossible" << std::endl;
	}

	return ;
}




void					Number::convert( void )
{

	std::regex		float_regex("((\\+|-)?\\d+\\.\\d+f)|-inff|\\+inff|nanf");
	std::regex		double_regex("((\\+|-)?\\d+\\.\\d+)|-inf|\\+inf|nan");
	std::regex		int_regex("(\\+|-)?(\\d)+");

	if( regex_match( this->getStr(), float_regex ) )
	{
		this->floatN = strtof( this->getStr().c_str(), NULL );
		this->type = FLOAT;
	}
	else if ( regex_match( this->getStr(), double_regex ) )
	{
		this->doubleN = strtod( this->getStr().c_str(), NULL );
		this->type = DOUBLE;
	}
	else if( regex_match( this->getStr(), int_regex ) )
	{
		this->intN = atoi( this->getStr().c_str() );
		this->type = INT;
	}
	else
	{
		this->type = NONE;
	}

//	this->toDouble();
//	this->toFloat();
//	this->toChar();
//	this->toInt();

	return;

}


std::ostream &		operator<<( std::ostream & out, Number const & operand )
{
	
	(void)out;
	operand.toChar();
	operand.toInt();
	operand.toFloat();
	operand.toDouble();
	return out;
}
