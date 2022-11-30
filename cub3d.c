/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/30 12:51:00 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	ft_esc(t_data *data)
{
	printf("bye :)\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit (0);
}

void	ft_end(t_data	data)
{
	mlx_hook(data.win_ptr, 2, 0, ft_event, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_esc, &data);
	mlx_loop(data.mlx_ptr);
}

void	ft_init(t_data	*data, t_cub3d *cubmap)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "cub3d");
	data->cub = cubmap;
	data->angle = (float)(1.5 * M_PI);
	data->p1.x = cubmap->pos_player_x * GRID_SIZE;
	data->p1.y = cubmap->pos_player_y * GRID_SIZE;
	data->p2.x = cubmap->pos_player_x * GRID_SIZE + cos(data->angle) * 20;
	data->p2.y = cubmap->pos_player_y * GRID_SIZE + sin(data->angle) * 20;
	data->key_press = -1;
}

void	ft_main(t_data	*data)
{
	create_image(data);
}
