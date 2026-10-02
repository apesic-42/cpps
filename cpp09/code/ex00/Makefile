NAME	:= btc
FLAGS	:= -Wall -Werror -Wextra -std=c++98
SRC	:= BitcoinExchange.cpp main.cpp
HDR	:= BitcoinExchange.hpp

all: $(NAME)

bonus: $(NAME)

clean:
	@rm -rf $(NAME).dSYM

debug: fclean
	@c++ $(FLAGS) -fsanitize=address -g $(SRC) -o $(NAME)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

$(NAME): $(SRC) $(HDR)
	@c++ $(FLAGS) $(SRC) -o $(NAME)

.PHONY: all bonus clean debug fclean re
