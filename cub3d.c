/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/12/09 12:32:33 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	ft_esc(t_data *data)
{
	printf("bye :)\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit (0);
}

int	ft_test(int keycode, t_data *data)
{
	if (ft_handle_oriented_event(data, keycode))
		data->key_to_oriented = -1;
	if (ft_handle_move_event(data, keycode))
		data->key_to_move = -1;
	return 0;
}

int	render_next_frame(t_data *data)
{
	// static int i;
	if (data->key_to_move != -1 || data->key_to_oriented != -1)
	{
		ft_oriented(data);
		ft_move(data);
		create_image(data);
	}

	return 1;
}

void	ft_end(t_data	data)
{
	mlx_hook(data.win_ptr, 2, 1L<<0, ft_event, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, ft_test, &data);

	mlx_hook(data.win_ptr, 17, 0, ft_esc, &data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
}

double ft_init_direction(char direction)
{
	if (direction == 'E')
		return (0);
	if (direction == 'N')
		return (M_PI_2);
	if (direction == 'S')
		return (1.5 * M_PI);
	return (M_PI);
}


void	ft_init(t_data	*data, t_cub3d *cubmap)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->cub = cubmap;
	data->angle = ft_init_direction(cubmap->direction);
	data->p1.x = cubmap->pos_player_x * GRID_SIZE;
	data->p1.y = cubmap->pos_player_y * GRID_SIZE;
	data->p2.x = (cubmap->pos_player_x * GRID_SIZE) + (cos(data->angle) * 20);
	data->p2.y = (cubmap->pos_player_y * GRID_SIZE) + (sin(data->angle) * 20);
	data->key_press = -1;
	data->key_to_move = -1;
	data->key_to_oriented = -1;
}

void	ft_main(t_data	*data)
{
	create_image(data);
}
