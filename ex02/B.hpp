#ifndef B_HPP
# define B_HPP

# include <iostream>
# include "Base.hpp"

class B: public Base
{

public:

	B( void );
	B( const B &src );
	~B( void );

	B	&operator=( const B &obj );

private:

};

std::ostream	&operator<<( std::ostream &ostr, const B &instance );

#endif
