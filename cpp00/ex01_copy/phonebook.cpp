
#include <iostream>
#include "_Contact.hpp"
#include "_PhoneBook.hpp"
#include <cstring>
#include <string>



int main(void){

    PhoneBook repertoire;
    repertoire.index = 0;

    std::string in;
    std::cout << "Hi welcome to phone book" << std::endl << std::endl;

    while (true)
    {
        std::cout << "please choose :" << std::endl << "1 : ADD" << std::endl << "2 : SEARCH" << std::endl << "3 : EXIT" << std::endl;

        std::getline(std::cin, in);
        if (in == "ADD")
            repertoire.add_contact();

    }
    return 0;

}
