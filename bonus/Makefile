NAME = cub3D

NAME_BONUS = cub3D_bonus

INC = include/cub3d.h

CC = cc 

FLAGS = -Wall -Wextra -Werror -g

fLIB = libft/

MA = ma/

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRC = cub3d.c \
	cub3d_2.c \
	get_next_line.c \
	utils/utils.c  \
	utils/ft_split.c \
	src/check_map1.c \
	src/check_map2.c \
	src/check_map_utils.c \
	src/check_map_utils2.c \
	src/check_map_utils3.c \
	src/check_errors_map.c \
	$(fLIB)ft_atoi.c \
	$(fLIB)ft_calloc.c \
	$(fLIB)ft_strstr.c \
	$(fLIB)ft_itoa.c \
	$(fLIB)ft_putendl_fd.c \
	$(fLIB)ft_putstr_fd.c \
	$(fLIB)ft_strchr.c \
	$(fLIB)ft_strdup.c \
	$(fLIB)ft_strjoin.c \
	$(fLIB)ft_strtrim.c \
	$(fLIB)ft_isdigit.c \
	$(fLIB)ft_substr.c \
	$(fLIB)ft_strcmp.c \
	$(MA)utils.c \
	$(MA)utils2.c \
	$(MA)image.c \
	$(MA)rays.c \
	$(MA)rays2.c \
	$(MA)rays_3.c \
	$(MA)render_3d.c \
	$(MA)mini_map.c \
	$(MA)utils_mini_map.c \
	$(MA)utils_mini_map2.c \
	main.c

OBJ = $(SRC:.c=.o)

$(NAME): 
	@echo "use :  make bonus";

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@
bonus: $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit  -o $(NAME_BONUS)
	@echo "$(COLOUR_GREEN)successfully compile ..."  $(NAME_BONUS)
	
clean : 
	@ rm -rf $(OBJ)
	@echo "$(COLOUR_RED)removed "

fclean : clean
	@rm -rf $(NAME_BONUS)
	@echo "$(COLOUR_RED)removed " $(NAME_BONUS)

re : fclean bonus