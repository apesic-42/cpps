NAME = phonebook

CC = g++
FLAGS = --std=c++98 -Wall -Wextra -Werror

SRCS = _Contact.cpp _Contact.hpp phonebook.cpp _PhoneBook.cpp _PhoneBook.hpp
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
