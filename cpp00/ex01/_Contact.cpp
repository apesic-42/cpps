/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Contact.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:36:20 by apesic            #+#    #+#             */
/*   Updated: 2025/10/20 11:36:21 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include <iostream>
#include <string>
#include <cstring>

#include "_Contact.hpp"

bool is_good(std::string a)
{
	if (a.size() < 2 || a.size() > 150)
		return false;
	return true;
}

bool Contact::set_first_name(void)
{
	std::string inn;

	std::cout << "enter a first name" << std::endl;

	if (!std::getline(std::cin, inn))
        return false;
	if (is_good(inn) == false)
	{
		std::cout << "resonnable first name" << std::endl;
		return false;
	}
	else
		this->first_name = inn;
	std::cout << this->first_name << std::endl;
	return true;

}


bool Contact::set_last_name(void)
{
	std::string inn;

	std::cout << "enter a last  name" << std::endl;

	if (!std::getline(std::cin, inn))
        return false;
	if (is_good(inn) == false)
	{
		std::cout << "resonnable last name" << std::endl;
		return false;
	}
	else
	    this->last_name = inn;
	std::cout << this->last_name << std::endl;
	return true;

}


bool Contact::set_phone_number(void)
{
	std::string inn;

	std::cout << "enter a phone number" << std::endl;

	if (!std::getline(std::cin, inn))
        return false;
	if (is_good(inn) == false)
	{
		std::cout << "A PHONE NUMBER" << std::endl;
		return false;
	}
	else
	    this->phone_number = inn;
	std::cout << this->phone_number << std::endl;
	return true;
}


bool Contact::set_nickname(void)
{
	std::string inn;

	std::cout << "enter a nickname" << std::endl;

	if (!std::getline(std::cin, inn))
        return false;
	if (is_good(inn) == false)
	{
		std::cout << "a resonnable nickname" << std::endl;
		return false;
	}
	else
		this->nickname = inn;
	std::cout << this->nickname << std::endl;
	return true;

}


bool Contact::set_darkest_secret(void)
{
	std::string inn;

	std::cout << "and now, be discret and enter your darkest secret" << std::endl;

	if (!std::getline(std::cin, inn))
        return false;
	if (is_good(inn) == false)
	{
		std::cout << "that bad, please more darkest" << std::endl;
		return false;
	}
	else
		this->darkest_secret= inn;
	std::cout << this->darkest_secret << std::endl;
	return true;

}

std::string  Contact::get_first_name(void){return this->first_name;}
std::string  Contact::get_last_name(void){return this->last_name;}
std::string  Contact::get_phone_number(void){return this->phone_number;}
std::string  Contact::get_nickname(void){return this->nickname;}
std::string  Contact::get_darkest_secret(void){return this->darkest_secret;}
