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

		void				convert( void ) const;

		class				ImpossibleException : public std::exception {
			public: virtual const char *what() const throw(); };
		class				NonDisplayableException : public std::exception {
			public: virtual const char *what() const throw(); };

	private:

		std::string const	_str;
		char				_charN;
		int					_intN;
		float				_floatN;
		double				_doubleN;
		e_type				_type;

		void				acquire( void );



};


#endif
