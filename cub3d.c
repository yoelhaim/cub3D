/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/12/17 22:06:14 by matef            ###   ########.fr       */
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

void	ft_oriented_2(t_data *data, int keycode)
{
	char	**map;
	double	*pa;

	pa = &data->angle;
	map = data->cub->maps;
	if (keycode == RIGHT_ARROW)
	{
		*pa += 0.03;
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
	if (keycode == LEFT_ARROW)
	{
		*pa -= 0.03;
		*pa = norm_angle(*pa);
		data->p2.x = data->p1.x + cos(*pa) * 20;
		data->p2.y = data->p1.y + sin(*pa) * 20;
	}
}


int ft_mouse(int x, int y, t_data *data)
{
	static int old_x;
// data->mouse_presed &&
	if ( 0 <= x && x <= WINDOW_WIDTH && 0 <= y && y <= WINDOW_HEIGHT)
	{
		if (old_x < x)
		{
			old_x = x;
			//ft_handle_oriented_event(data, RIGHT_ARROW);
			// printf("right x = %d\n", x);
			ft_oriented_2(data, RIGHT_ARROW);
			
			create_image(data);
			return 0;
		}
		else if (old_x > x)
		{
			old_x = x;
			ft_oriented_2(data, LEFT_ARROW);
			
			create_image(data);
			
			//ft_handle_oriented_event(data, LEFT_ARROW);
			// printf("left x = %d\n", x);
			return 0;
		}
	}
	// printf("ffff\n");
	data->key_to_oriented = -1;
	return 0;
}

int ft_mouse_down(t_data *data)
{
	printf("gg %d\n", data->key_to_move);

	// data->mouse_presed = 1;
	return 0;
}

// int ft_mouse_up(t_data *data)
// {
// 	// data->mouse_presed = 0;
// 	return 0;
// }

void	ft_end(t_data	data)
{
	mlx_hook(data.win_ptr, 2, 1L<<0, ft_event, &data);
	mlx_hook(data.win_ptr, 3, 1L<<1, ft_test, &data);

	mlx_hook(data.win_ptr, 6,0, ft_mouse, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_esc, &data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
}

double ft_init_direction(char direction)
{
	if (direction == 'E')
		return (0);
	else if (direction == 'N')
		return (1.5 * M_PI);
	else if (direction == 'S')
		return (M_PI_2);
	return (M_PI);
}


void	ft_init(t_data	*data, t_cub3d *cubmap)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data->cub = cubmap;
	data->angle = ft_init_direction(cubmap->direction);
	data->p1.x = (cubmap->pos_player_x * GRID_SIZE) + (GRID_SIZE / 2);
	data->p1.y = (cubmap->pos_player_y * GRID_SIZE) + (GRID_SIZE / 2);
	data->p2.x = (cubmap->pos_player_x * GRID_SIZE) + (cos(data->angle) * 20);
	data->p2.y = (cubmap->pos_player_y * GRID_SIZE) + (sin(data->angle) * 20);
	data->key_press = -1;
	data->key_to_move = -1;
	data->key_to_oriented = -1;
	// data->mouse_presed = 0;
}

void	ft_main(t_data	*data)
{
	create_image(data);
}
