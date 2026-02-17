SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/Animal.cpp \
      $(SRC_DIR)/Brain.cpp \
      $(SRC_DIR)/Cat.cpp \
      $(SRC_DIR)/Dog.cpp

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
CC = c++
RM = rm -f
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)

NAME = animals

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
