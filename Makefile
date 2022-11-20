NAME = Cub3d
INC = include/cub3d.h
CC = cc 
FLAGS = -Wall -Wextra -Werror
SRC = cub3d.c get_next_line.c \
	utils/utils.c  \
	utils/ft_split.c \
	utils/ft_strtrim.c \
	src/check_map1.c \
	src/check_map2.c \
	src/check_errors_map.c

SRC_UTILS = utils/utils.c \
	get_next_line.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
all : $(NAME)
%.o : %.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@
clean : 
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean all