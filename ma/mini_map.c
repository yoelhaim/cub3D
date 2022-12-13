/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:03:08 by matef             #+#    #+#             */
/*   Updated: 2022/12/13 19:56:31 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double ft_grid(double x)
{
	return ((GRID_SIZE * x));
}

static t_rect ft_rect(double j, double i, int color)
{
	return ((t_rect){ft_grid(j), ft_grid(i), ft_grid(1), ft_grid(1), color});
}

void draw_map(t_data *data)
{
	int i;
	int j;
    char **map;
    
	i = 0;
	map = data->cub->maps;
    while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				render_rect(&data->img, ft_rect(j, i, WALL));
			else if (map[i][j] == '0')
				render_rect(&data->img, ft_rect(j, i, SPACE));
			j++;
		}
		i++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void ft_mini_map(t_data *data)
{
    // draw_map(data, data->cub->maps);
	int i;
	int j;

	i = 15;
	while (i < 200)
	{
		j = WINDOW_HEIGHT - 200;
		while (j < WINDOW_HEIGHT - 15)
		{
			img_pix_put(&data->img, i, j, create_trgb(1, 50, 64, 123));
			j++;
		}
		i++;
	}
    // draw_map(data);
	//render_rect(&data->img, (t_rect){data->p1.x / 10, data->p1.y / 10, 5, 5, YELLOW});
	// DDA2(data, data->p1, data->p2);
}