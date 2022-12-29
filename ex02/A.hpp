#ifndef A_HPP
# define A_HPP

# include <iostream>
# include "Base.hpp"

class A: public Base
{

public:

	A( void );
	A( const A &src );
	~A( void );

	A	&operator=( const A &obj );

private:

};

std::ostream	&operator<<( std::ostream &ostr, const A &instance );

#endif

