/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:35:40 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 23:05:36 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d_bonus.h"

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
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->key_to_move != -1 || data->key_to_oriented != -1)
	{
		ft_oriented(data);
		ft_move(data);
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		create_image(data);
	}
	return (1);
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

int	ft_mouse(int x, int y, t_data *data)
{
	static int	old_x;

	if (0 <= x && x <= WINDOW_WIDTH && 0 <= y && y <= WINDOW_HEIGHT)
	{
		if (old_x < x)
		{
			old_x = x;
			ft_oriented_2(data, RIGHT_ARROW);
			create_image(data);
			return (0);
		}
		else if (old_x > x)
		{
			old_x = x;
			ft_oriented_2(data, LEFT_ARROW);
			create_image(data);
			return (0);
		}
	}
	data->key_to_oriented = -1;
	return (0);
}
