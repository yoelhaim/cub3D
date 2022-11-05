NAME = Cub3d
INC = include/cub3d.h
CC = cc 
FLAGS = -Wall -Wextra -Werror
SRC = cub3d.c 
SRC_UTILS = utils/utils1.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
all : $(NAME)
%.o : %.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@
clean : 
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean all