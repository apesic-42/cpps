/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _Contact.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:36:05 by apesic            #+#    #+#             */
/*   Updated: 2025/10/20 11:41:28 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string>

#ifndef CONTACT_HPP
#define CONTACT_HPP

class Contact{
	private :
		std::string  first_name;
		std::string  last_name;
		std::string  phone_number;
		std::string  nickname;
		std::string  darkest_secret;
	public :
		bool set_first_name(void);
		bool set_last_name(void);
		bool set_phone_number(void);
		bool set_nickname(void);
		bool set_darkest_secret(void);

		std::string  get_first_name(void);
		std::string  get_last_name(void);
		std::string  get_phone_number(void);
		std::string  get_nickname(void);
		std::string  get_darkest_secret(void);
};

#endif
