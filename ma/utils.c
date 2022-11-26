/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:20 by matef             #+#    #+#             */
/*   Updated: 2022/11/26 18:08:12 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_oriented(int keycode, t_data *data)
{
	char **map;
	float *pa;

	pa = &data->angle;
	map = data->cub->maps;
	if (keycode == 124)
	{
		*pa -= 0.1;
		
		if (*pa < 0)
			*pa = 2 * M_PI;
		
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
		return ;
	}
	if (keycode == 123)
	{
		*pa += 0.1;
		
		if (*pa > 2 * M_PI)
			*pa = 0;

		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
		return ;
	}
}


int ft_event(int keycode, t_data *data)
{
	double x;
	double y;

	x = data->cub->pos_player_x;
	y = data->cub->pos_player_y;
	if (keycode == 53)
		ft_esc(data);
	ft_oriented(keycode, data);
	ft_move(keycode, data);
	create_image(data);
	return (0);
}

void	ft_move(int keycode, t_data *data)
{
	char **map;
	float *pa;

	pa = &data->angle;
	map = data->cub->maps;
	int i;
	int j;

	// printf("%d\n", keycode);
	if (keycode == 13)
	{
		i = data->p1.x + cos(*pa) * 2;
		j = data->p1.y + sin(*pa) * 2;
		if (map[j / GRID_SIZE][i / GRID_SIZE] != '1')
		{
			data->p1.x += cos(*pa) * 2;
			data->p2.x += cos(*pa) * 2;
			data->p1.y += sin(*pa) * 2;
			data->p2.y += sin(*pa) * 2;
		}
	}
	else if (keycode == 1)
	{
		i = data->p1.x - cos(*pa) * 2;
		j = data->p1.y - sin(*pa) * 2;
		if (map[j / GRID_SIZE][i / GRID_SIZE] != '1')
		{
			data->p1.x -= cos(*pa) * 2;
			data->p2.x -= cos(*pa) * 2;
			data->p1.y -= sin(*pa) * 2;
			data->p2.y -= sin(*pa) * 2;
		}
	}
	else if (keycode == 2)
	{
		i = data->p1.x + cos(*pa) * 2;
		j = data->p1.y - sin(*pa) * 2;
		if (map[j / GRID_SIZE][i / GRID_SIZE] != '1')
		{
			data->p1.x -= sin(*pa) * 2;
			data->p2.x -= sin(*pa) * 2;
			data->p1.y += cos(*pa) * 2;
			data->p2.y += cos(*pa) * 2;
		}
	}
	else if (keycode == 0)
	{
		i = data->p1.x - cos(*pa) * 2;
		j = data->p1.y + sin(*pa) * 2;
		if (map[j / GRID_SIZE][i / GRID_SIZE] != '1')
		{
			data->p1.x += sin(*pa) * 2;
			data->p2.x += sin(*pa) * 2;
			data->p1.y -= cos(*pa) * 2;
			data->p2.y -= cos(*pa) * 2;
		}
	}
}

