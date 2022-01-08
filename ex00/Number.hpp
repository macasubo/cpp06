#ifndef NUMBER_H
# define NUMBER_H

#include <string>


enum	e_type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	NONE
};

class	Number
{
	public:

		Number( void );
		Number( std::string const & str );
		Number( Number const & src );
		~Number( void );

		Number &			operator=( Number & operand );

		std::string const &	getStr( void ) const;

		void				toChar( void ) const;
		void				toInt( void ) const;
		void				toDouble( void ) const;
		void				toFloat( void ) const;

		class				ImpossibleException : public std::exception {};
		class				NonDisplayableException : public std::exception {};

		char				charN;
		int					intN;
		float				floatN;
		double				doubleN;


	private:

		std::string const	str;
		double				number;
		e_type				type;
		void				convert( void );


};

std::ostream &				operator<<( std::ostream & out, Number const & operand );

#endif
