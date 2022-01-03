#ifndef NUMBER_H
# define NUMBER_H

#include <string>

class	Number
{
	public:

		Number( void );
		Number( std::string const & str );
		Number( Number const & src );
		~Number( void );

		Number &			operator=( Number & operand );

		std::string const &	getStr( void ) const;

	private:

		std::string const	name;

		char				toChar( void ) const;
		int					toInt( void ) const;
		double				toDouble( void ) const;
		float				toFloat( void ) const;

};

std::ostream &				operator<<( std::ostream & out, Number const & operand );

#endif
