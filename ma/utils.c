/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:20 by matef             #+#    #+#             */
/*   Updated: 2022/11/23 15:35:03 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print_grid(t_vars *vars)
{
	int x = 30;
	int y = 30;
	while (x < 1080)
	{
		print_line(vars, x);
		x += 30;
	}
	while (y < 1920)
	{
		print_col(vars, y);
		y += 30;
	}
}

void print_line(t_vars *vars, int x)
{
	int y = -1;
	while (++y < 1920)
		mlx_pixel_put(vars->mlx, vars->win, y, x, 0x352F44);
}

void print_col(t_vars *vars, int y)
{
	int x = -1;
	while (++x < 1080)
		mlx_pixel_put(vars->mlx, vars->win, y, x, 0x352F44);
}

// void move(t_vars *vars, int y, int x)
// {
	
// 	print_squre(vars->mlx, vars->win, y, x, 0xFF0000);
// 	// mlx_pixel_put(vars->mlx, vars->win, y, x, 0xF0FF42);
// }

int ft_oriented(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 124)
	{
		printf("hello\n");
		return 1;
	}

	return 0;
}

int ft_event(int keycode, t_data *data)
{
	double x;
	double y;

	x = data->cub->pos_player_x;
	y = data->cub->pos_player_y;
	if (keycode == 53)
		ft_esc(data);
	if (!ft_oriented(keycode, data))
		ft_move(keycode, data, y, x);
	return (0);
}

void	ft_move(int keycode, t_data *data, double y, double x)
{
	char **map;
	
	map = data->cub->maps;
	printf("%d\n", keycode);
	if (keycode == 2)
	{
		if (map[(int)y][(int)(x + 0.2)] == '0')
		{
			data->cub->pos_player_x += 0.2;
			// mlx_destroy_image(data->mlx_ptr, &data->img);
			create_image(data);
		}
	}
	if (keycode == 13)
	{
		if (map[(int)(y - 0.2)][(int)x] == '0')
		{
			data->cub->pos_player_y -= 0.2;
			// mlx_destroy_image(data->mlx_ptr, &data->img);
			create_image(data);
		}
	}
	if (keycode == 0)
	{
		if (map[(int)y][(int)(x - 0.2)] == '0')
		{
			data->cub->pos_player_x -= 0.2;
			// mlx_destroy_image(data->mlx_ptr, &data->img);
			create_image(data);
		}
	}
	if (keycode == 1)
	{
		if (map[(int)(y + 0.2)][(int)x] == '0')
		{
			data->cub->pos_player_y += 0.2;
			// mlx_destroy_image(data->mlx_ptr, &data->img);
			create_image(data);
		}
	}
}

