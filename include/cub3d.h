/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:56:24 by pro               #+#    #+#             */
/*   Updated: 2022/11/20 22:43:56 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <mlx.h>
# define WIDTH 900
# define HEIGHT 750



typedef struct s_cub3d
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char **map;
	char **maps;
	int floor[3];
	int ciel[3];
	int last_index;
	unsigned int pos_player_x;
	unsigned int pos_player_y;
} t_cub3d;

// mlx
typedef struct	s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_mlx;
// libft_functions
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlen(const char *s);
void *ft_memcpy(void *dst, const void *src, size_t n);
char **ft_split(char const *s, char c);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
char *ft_strdup(const char *s1);
char *ft_strtrim(char const *s1, char const *set);
// getnext line
char *get_next_line(int fd);
// utils
size_t ft_len_ptr(char **ptr);
// check map 1
int check_exten(char *filename);
int check_name_exc(char *filename);
int read_to_file(char *namefile, t_cub3d *cubmap);
char **remove_empty_line(char **map);
// check errors

int check_colors_floor(char *color, t_cub3d *cubmap);
int check_colors_ciel(char *color, t_cub3d *cubmap);
int check_floor_ceil(int *str);
int check_file_texture(t_cub3d *texture);
/// maps
int check_maps(t_cub3d *cubmap, char *namefile);
int check_is_valid_map(char **maps, t_cub3d *cubmap);
#endif