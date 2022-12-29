#include <iostream>
#include <stdint.h>
#include "structs.hpp"

void print_obj( Data obj)
{
	std::cout << &obj << ", " <<
	 " sizeof( obj )  = " << sizeof(obj) << std::endl;
	return ;
}

// void pritn_members ( )

uintptr_t	serialize(Data *ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data	*deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data *>(raw);
}

int	main( void )
{
	Data		*ptr = new Data;
	Data		*new_ptr;
	uintptr_t	raw;

	std::cout << "sizeof( std::string) = " << sizeof(std::string) << std::endl;
	std::cout << "sizeof( uintptr_t) = " << sizeof(uintptr_t) << std::endl;
	ptr->data = "Hi, how's going ";
	raw = serialize(ptr);
	std::cout << "ptr serialized( ptr ) ," << "sizeof( raw ) = " << sizeof(raw) << std::endl;
	std::cout << "raw.data is not able to access cause it has been reintreptet_cast to 'uintptr_t'. " << std::endl; 

	new_ptr = deserialize(raw);
	std::cout << "new_ptr deserialized( raw ) ," << "sizeof( raw ) = " << sizeof(new_ptr) << std::endl;
	std::cout << "now new_ptr.data is able to access cause it has been reintreptet_cast to 'Data'. " << std::endl;
	print_obj(*ptr);
	std::cout << "new_ptr->data = " << new_ptr->data << std::endl;

}
