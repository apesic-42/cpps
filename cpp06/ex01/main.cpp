
#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int	main()
{
	Data		*ptr;
	Data		*new_ptr;
	uintptr_t	raw;

	ptr = new Data;
	ptr->data = "Fake Data!";

	raw = Serializer::serialize(ptr);
	new_ptr = Serializer::deserialize(raw);

	std::cout << "Data of ptr: " << ptr->data << std::endl;
	std::cout << "Data of new_ptr: " << new_ptr->data << std::endl;

	if (ptr == new_ptr)
		std::cout << "Pointers are equal!" << std::endl;
	else
		std::cout << "Pointers are NOT equal!" << std::endl;

	delete ptr;
}
