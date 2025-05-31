NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c
SRC_PATH = source
OBJ_PATH = obj
OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)


$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH) 
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
#	@echo "SUCCESS"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH)
	@echo CLEANED SUCCESSFULLY

all: $(NAME)
	@echo "SUCCESSFULLY CREATED ./philo"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean
