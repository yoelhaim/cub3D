/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:20 by matef             #+#    #+#             */
/*   Updated: 2022/12/07 11:55:50 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int ft_handle_move_event(t_data *data, int keycode)
{
	if (keycode == A_KEY || keycode == D_KEY || keycode == S_KEY || keycode == W_KEY )
	{
		data->key_to_move = keycode;
		return 1;
	}
	return 0;
}

int ft_handle_oriented_event(t_data *data, int keycode)
{
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
	{
		data->key_to_oriented = keycode;
		return 1;
	}
	return 0;
}

void	ft_oriented(int keycode, t_data *data)
{
	char	**map;
	double	*pa;

	(void)keycode;
	pa = &data->angle;
	map = data->cub->maps;
	if (data->key_to_oriented == RIGHT_ARROW)
	{
		*pa += 0.1;
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
	else if (data->key_to_oriented == LEFT_ARROW)
	{
		*pa -= 0.1;	
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
	printf("oriented key_1 %d, key_2 %d\n", data->key_to_move, data->key_to_oriented);
	//return ft_oriented(keycode, data);
}

int ft_is_wall_2(char **map, int i, int j, t_point *p)
{
	int x;
	int y;

	x = (int)floor(j / GRID_SIZE);
	y = (int)floor(i / GRID_SIZE);

	// if (x < 0 || x > x11 || y < 0 || y > y11)
	// 	return 1;
	if (map[x][y] == '0')
	{
		p->x = x;
		p->y = y;
		return (1);
	}

	return (0);
}

int	ft_is_wall(char **map, int i, int j)
{
	int x;
	int y;

	x = (int)floor(j / GRID_SIZE);
	y = (int)floor(i / GRID_SIZE);

	// if (x < 0 || x > x11 || y < 0 || y > y11)
	// 	return 1;

	//printf("x = %d x11 == %d \ny = %d y11 = %d\n\n", x, x11, y, y11);
	
	
	// if (x <= x11 || y <= y11)
		return (map[x][y] == '0');
	// return(0);
}

int	ft_event(int keycode, t_data *data)
{
	double	x;
	double	y;

	x = data->cub->pos_player_x;
	y = data->cub->pos_player_y;
	if (keycode == ESC)
		ft_esc(data);
	ft_handle_move_event(data, keycode);
	ft_handle_oriented_event(data, keycode);
	ft_oriented(keycode, data);
	ft_move(keycode, data);
	create_image(data);
	return (0);
}

void	ft_move_up(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x + cos(pa) * MOVE_STEP;
	j = data->p1.y + sin(pa) * MOVE_STEP;
	if (ft_is_wall(map, i, j))
	{
		data->p1.x += cos(pa) * MOVE_STEP;
		data->p2.x += cos(pa) * MOVE_STEP;
		data->p1.y += sin(pa) * MOVE_STEP;
		data->p2.y += sin(pa) * MOVE_STEP;
	}
}

void	ft_move_down(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x - cos(pa) * MOVE_STEP;
	j = data->p1.y - sin(pa) * MOVE_STEP;
	if (ft_is_wall(map, i, j))
	{
		data->p1.x -= cos(pa) * MOVE_STEP;
		data->p2.x -= cos(pa) * MOVE_STEP;
		data->p1.y -= sin(pa) * MOVE_STEP;
		data->p2.y -= sin(pa) * MOVE_STEP;
	}
}

void	ft_move_left(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x - cos(pa) * MOVE_STEP;
	j = data->p1.y + sin(pa) * MOVE_STEP;
	if (ft_is_wall(map, i, j))
	{
		data->p1.x += sin(pa) * MOVE_STEP;
		data->p2.x += sin(pa) * MOVE_STEP;
		data->p1.y -= cos(pa) * MOVE_STEP;
		data->p2.y -= cos(pa) * MOVE_STEP;
	}
}

void	ft_move_right(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x + cos(pa) * MOVE_STEP;
	j = data->p1.y - sin(pa) * MOVE_STEP;
	if (ft_is_wall(map, i, j))
	{
		data->p1.x -= sin(pa) * MOVE_STEP;
		data->p2.x -= sin(pa) * MOVE_STEP;
		data->p1.y += cos(pa) * MOVE_STEP;
		data->p2.y += cos(pa) * MOVE_STEP;
	}
}

void	ft_move(int keycode, t_data *data)
{
	char	**map;
	double	*pa;

	(void)keycode;
	pa = &data->angle;
	map = data->cub->maps;
	if (data->key_to_move == W_KEY)
		ft_move_up(data, map, data->angle);
	else if (data->key_to_move == S_KEY)
		ft_move_down(data, map, data->angle);
	else if (data->key_to_move == D_KEY)
		ft_move_right(data, map, data->angle);
	else if (data->key_to_move == A_KEY)
		ft_move_left(data, map, data->angle);
	
	printf("move key_1 %d, key_2 %d\n", data->key_to_move, data->key_to_oriented);
}
