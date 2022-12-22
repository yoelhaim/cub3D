/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:35:40 by matef             #+#    #+#             */
/*   Updated: 2022/12/22 19:07:15 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	ft_esc(t_data *data)
{
	printf("Game Over 👋\n");
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit (0);
}

// int	ft_handle_move_r_l(t_data *data, int keycode)
// {
// 	if (keycode == A_KEY || keycode == D_KEY)
// 	{
// 		data->key_to_move_left = keycode;
// 		return (1);
// 	}
// 	return (0);
// }

int	ft_test(int keycode, t_data *data)
{
	if (ft_handle_move_r_l(data, keycode))
		data->key_to_move_left = -1;
	if (ft_handle_oriented_event(data, keycode))
		data->key_to_oriented = -1;
	if (ft_handle_move_event(data, keycode))
		data->key_to_move = -1;
	return (0);
}

int	render_next_frame(t_data *data)
{
	if (data->key_to_move != -1 || data->key_to_oriented != -1 || data->key_to_move_left != -1)
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
