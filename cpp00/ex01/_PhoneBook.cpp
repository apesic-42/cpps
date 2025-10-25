/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _PhoneBook.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:36:24 by apesic            #+#    #+#             */
/*   Updated: 2025/10/20 11:54:32 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "_PhoneBook.hpp"

int PhoneBook::count_add_contact()
{
	if (this->count > 7)
	{
		this->count = 0;
	}
	return this->count;
}

void PhoneBook::add_contact()
// Si l utilisateur entre cette commande, le programme lui demande de remplir
// une par une les informations du nouveau contact. Une fois tous les champs
// complétés, le nouveau contact est ajouté au répertoire.

// Un contact possède les champs suivants : first name (prénom), last name
// (nom de famille), nickname (surnom), phone number (numéro de téléphone),
// et darkest secret (son plus lourd secret). Les champs d un contact enregistré ne
// peuvent être vides.
{
	Contact un;
	bool ok = false;
	while(ok == false)
	{
		ok = un.set_first_name();
	}
	ok = false;
	while(ok == false)
	{
		ok = un.set_last_name();
	}
	ok = false;
	while(ok == false)
	{
		ok = un.set_nickname();
	}
	ok = false;
	while(ok == false)
	{
		ok = un.set_phone_number();
	}
	ok = false;
	while(ok == false)
	{
		ok = un.set_darkest_secret();
	}
	std::cout << "contact added" << std::endl;
	// erreur si on arrive au dessus de 8 (ca efface tous)
	bool DONT_INCR;
	if (this->index > 7)
	    DONT_INCR = true;
	this->contact[count_add_contact()] = un;
	if (!DONT_INCR)
	    this->index++;
	this->count++;
};


std::string get_segment(std::string remplacement)
{
    std::string remplacementt;

    if (remplacement.size() > 10)
        remplacementt = remplacement.substr(0, 9) + ".";
    else
    {
        remplacementt = remplacement;
    }

    return std::string(10 - remplacementt.size(),' ') + remplacementt;
}

std::string get_line(Contact contact, int index)
{
    std::string ret;
    std::stringstream ss;
    ss << index;

    std::string ind = "         " + ss.str();
    std::string fn = "|" + get_segment(contact.get_first_name());
    std::string ln = "|" + get_segment(contact.get_last_name());
    std::string nn = "|" + get_segment(contact.get_nickname());
    return (ind + fn + ln + nn);
}



bool type_ok(std::string index_choisit)
{
    for (size_t i = 0; i < index_choisit.size(); i++)
    {
        if(!isdigit(index_choisit[i]))
            return false;
    }
    return true;
}

void PhoneBook::search_contact()
{
    int nombre;
    if (this->index <= 0)
        std::cout << "You have " << this->index << "contacts, please before upload contacts." << std::endl;

    for (int i = 0; i < this->index; i++)
    {
        std::cout << get_line(this->contact[i], i) << std::endl;
    }
    std::string index_choisit;
    if (!std::getline(std::cin, index_choisit))
        return;
    if (!type_ok(index_choisit))
    {
        std::cout << "type please type a number" << std::endl;
        return;
    }
    for(int i = 0; i < this->index; i++)
    {
        std::istringstream ss(index_choisit);
        ss >> nombre;
        if (i == nombre)
        {
            std::cout << "first name :" << this->contact[nombre].get_first_name() << std::endl;
            std::cout << "last name :" << this->contact[nombre].get_last_name() << std::endl;
            std::cout << "nickname :" << this->contact[nombre].get_nickname() << std::endl;
            std::cout << "phone number :" << this->contact[nombre].get_phone_number() << std::endl;
            std::cout << "Darkest secret :" << this->contact[nombre].get_darkest_secret() << std::endl;
            return;
        }
    }
    std::cout << "Contact not found" << std::endl;



}
