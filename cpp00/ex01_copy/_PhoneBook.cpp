

#include <iostream>
#include "_PhoneBook.hpp"

int PhoneBook::count_add_contact()
{
	if (this->index > 7)
	{
		this->index = 0;
	}
	return this->index;
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
	this->contact[count_add_contact()] = un;
	std::cout << "contact added" << std::endl;
};

