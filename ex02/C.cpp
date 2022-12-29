#include "C.hpp"

C::C( void )
{
	std::cout << "Default constructor for C called" << std::endl;
	return;
}

C::C( C const & src )
{
	std::cout << "Copy constructor for C called" << std::endl;
	*this = src;
	return;
}

C::~C( void )
{
	return;
}

C &	C::operator=( C const & obj )
{
	(void)obj;
	std::cout << "Cssignement operator for C called" << std::endl;
	return *this;
}

std::ostream &	operator<<( std::ostream & ostr, C const & instance)
{
	(void)instance;
	ostr << "No value for C" << std::endl;
	return ostr;
}
