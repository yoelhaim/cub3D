/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:20 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 17:51:59 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_handle_move_event(t_data *data, int keycode)
{
	if (keycode == A_KEY || keycode == D_KEY || \
	keycode == S_KEY || keycode == W_KEY)
	{
		data->key_to_move = keycode;
		return (1);
	}
	return (0);
}

int	ft_handle_oriented_event(t_data *data, int keycode)
{
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
	{
		data->key_to_oriented = keycode;
		return (1);
	}
	return (0);
}

void	ft_oriented(t_data *data)
{
	char	**map;
	double	*pa;

	pa = &data->angle;
	map = data->cub->maps;
	if (data->key_to_oriented == RIGHT_ARROW)
	{
		*pa += 0.05;
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
	if (data->key_to_oriented == LEFT_ARROW)
	{
		*pa -= 0.05;
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
}

int	ft_is_wall(char **map, int i, int j)
{
	int	x;
	int	y;

	x = (int)floor(j / GRID_SIZE);
	y = (int)floor(i / GRID_SIZE);
	return (map[x][y] == '0');
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
	return (0);
}
