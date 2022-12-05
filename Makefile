NAME = cub3d

INC = include/cub3d.h

CC = cc 

FLAGS = -Wall -Wextra -Werror

fLIB = libft/

MA = ma/

SRC = cub3d.c get_next_line.c \
	utils/utils.c  \
	utils/ft_split.c \
	src/check_map1.c \
	src/check_map2.c \
	src/check_map_utils.c \
	src/check_map_utils2.c \
	src/check_errors_map.c \
	$(fLIB)ft_atoi.c \
	$(fLIB)ft_itoa.c \
	$(fLIB)ft_putendl_fd.c \
	$(fLIB)ft_putstr_fd.c \
	$(fLIB)ft_strchr.c \
	$(fLIB)ft_strdup.c \
	$(fLIB)ft_strjoin.c \
	$(fLIB)ft_strtrim.c \
	$(fLIB)ft_isdigit.c \
	$(fLIB)ft_substr.c \
	$(MA)utils.c \
	$(MA)image.c \
	$(MA)rays.c \
	$(MA)render_3d.c \
	main.c

SRC_UTILS = utils/utils.c \
	get_next_line.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -g -o $(NAME)

all : $(NAME)

%.o : %.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all