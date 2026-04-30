

C++_FLAGS = -Wall -Wextra -Werror -std=c++98
INFILES = 	main.cpp\
			Bureaucrat.cpp\

OBJFILES = $(INFILES:.cpp=.o)

NAME = bureaucrat

all: $(NAME)

$(NAME):$(OBJFILES)
	c++ $(C++_FLAGS) $(OBJFILES) -o $(NAME)

%.o: %.cpp
	c++ $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
