NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread

SRC = main.c utils.c input_check.c
SRC_PATH = source
OBJ_PATH = obj
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)

all: $(NAME)
	@echo "SUCCESSFULLY CREATED ./philo"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH) 
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo CLEANED SUCCESSFULLY

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean
