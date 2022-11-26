/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:56:24 by pro               #+#    #+#             */
/*   Updated: 2022/11/26 19:36:10 by matef            ###   ########.fr       */
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
#include <math.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
#define GREEN_PIXEL 0xFF00
#define RED 0xFF0000
#define WHITE_PIXEL 0xFFFFFF
#define WALL 0x5454C5
#define SPACE 0x639CD9
#define YELLOW 0xFFFF00
#define DARK 0x342056
#define GRID_SIZE 30

// #define PI = 3.14159


typedef struct s_point
{
	float x;
	float y;
} t_point;

typedef struct s_line
{
	int dx;
    int dy;
    int steps;
    float Xinc;
    float Yinc;
	float X;
	float Y;
} t_line;

typedef struct s_cub3d
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**map;
	char			**maps;
	int				floor[3];
	int				ciel[3];
	int				last_index;
	double			pos_player_x;
	double			pos_player_y;
	char			direction;
}	t_cub3d;
// mlx
typedef struct s_vars {
	void	*mlx;
	void	*win;
	int		pos_player_x;
	int		pos_player_y;
	t_cub3d *cub;
}	t_vars;
// libft_functions

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_cub3d *cub;
	t_point p1;
	t_point p2;
	float	angle;
	int key_press;
}	t_data;


typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_vector
{
	int origin_x;
	int origin_y;
	
} t_vector;

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
// getnext line
char	*get_next_line(int fd);
// utils
size_t	ft_len_ptr(char **ptr);
int		ft_is_digit(char *str);
// check map 1
int		check_exten(char *filename);
int		check_name_exc(char *filename);
int		read_to_file(char *namefile, t_cub3d *cubmap);
char	**remove_empty_line(char **map);
void	get_map(int size, int fd, t_cub3d *cubmap);
// check errors
int		check_colors_floor(char *color, t_cub3d *cubmap);
int		check_colors_ciel(char *color, t_cub3d *cubmap);
int		check_floor_ceil(int *str);
int		check_file_texture(t_cub3d *texture);
// maps
int		check_maps(t_cub3d *cubmap, char *namefile);
int		check_is_valid_map(char **maps, t_cub3d *cubmap);


void	move(t_data *data, int y, int x);
int		ft_esc(t_data *data);
int 	ft_event(int keycode, t_data *data);
void	ft_move(int keycode, t_data *data);
void	ft_oriented(int keycode, t_data *data);



void	ft_end(t_data	data);
void	ft_init(t_data	*data, t_cub3d *cubmap);
void	ft_main(t_data	*data);



void	img_pix_put(t_img *img, int x, int y, int color);
void    create_image(t_data *data);
int     render_rect(t_img *img, t_rect rect);
void	render_background(t_img *img, int color);
int	    render(t_data *data, char **map);

#endif
