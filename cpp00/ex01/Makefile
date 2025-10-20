# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apesic <apesic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 11:36:29 by apesic            #+#    #+#              #
#    Updated: 2025/10/20 11:36:30 by apesic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook

CC = g++
FLAGS = --std=c++98 -Wall -Wextra -Werror

SRCS = _Contact.cpp phonebook.cpp _PhoneBook.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
