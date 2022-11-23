/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/23 15:30:17 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int how_many_grid(int grid)
{
	return grid * 30;
}

int how_many_grid_mini(int grid)
{
	return grid * 10;
}


int	ft_esc(t_data *data)
{
	printf("bye :)\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit (0);
}


void ft_end(t_data	data)
{
	// print_grid(&data);
	
	mlx_hook(data.win_ptr, 2, 0, ft_event, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_esc, &data);
	mlx_loop(data.mlx_ptr);
}

void ft_init(t_data	*data, t_cub3d *cubmap)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "cub3d");
	data->cub = cubmap;
}

void print_squre(void *mlx, void *win, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(mlx, win, how_many_grid_mini(y) + i, how_many_grid_mini(x) + j, color);
			j++;
		}
		i++;
	}
}

void ft_main(t_data	*data)
{
	
	create_image(data);

}

void	handle_c(int pid)
{
	(void)pid;
	exit (0);
}




