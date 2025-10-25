/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:36:31 by apesic            #+#    #+#             */
/*   Updated: 2025/10/20 11:36:32 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "_Contact.hpp"
#include "_PhoneBook.hpp"
#include <cstring>
#include <string>



int main(void){

    PhoneBook repertoire;
    repertoire.index = 0;
    repertoire.count = 0;

    std::string in;
    std::cout << "Hi welcome to phone book" << std::endl << std::endl;

    while (true)
    {
        std::cout << "please choose :" << std::endl << "1 : ADD" << std::endl << "2 : SEARCH" << std::endl << "3 : EXIT" << std::endl;

        if (!std::getline(std::cin, in))
            break;
        if (in == "ADD")
            repertoire.add_contact();
        if (in == "SEARCH")
            repertoire.search_contact();
        if (in == "EXIT")
            break;

    }
    return 0;

}
