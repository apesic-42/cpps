NAME = span

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp Span.cpp

all: $(NAME)

$(NAME): $(SRCS) Span.hpp
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
