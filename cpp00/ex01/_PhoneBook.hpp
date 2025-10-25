/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _PhoneBook.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:36:26 by apesic            #+#    #+#             */
/*   Updated: 2025/10/20 11:54:10 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream>
#include "_Contact.hpp"


#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

class PhoneBook{
	private :
	 	Contact contact[8];

	public :
		int index; // to keep size of stack in reality
		int count; // to keep count, position of next add
		void add_contact();
		void search_contact();
		int count_add_contact();

};

#endif
