/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:28:20 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 17:51:51 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_move_up(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x + (cos(pa) * (MOVE_STEP * 3));
	j = data->p1.y + (sin(pa) * (MOVE_STEP * 3));
	if (ft_is_wall(map, i, j))
	{
		data->p1.x += cos(pa) * MOVE_STEP;
		data->p2.x += cos(pa) * MOVE_STEP;
		data->p1.y += sin(pa) * MOVE_STEP;
		data->p2.y += sin(pa) * MOVE_STEP;
	}
}

void	ft_move_down(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	i = data->p1.x - (cos(pa) * (MOVE_STEP * 3));
	j = data->p1.y - (sin(pa) * (MOVE_STEP * 3));
	if (ft_is_wall(map, i, j))
	{
		data->p1.x -= cos(pa) * MOVE_STEP;
		data->p2.x -= cos(pa) * MOVE_STEP;
		data->p1.y -= sin(pa) * MOVE_STEP;
		data->p2.y -= sin(pa) * MOVE_STEP;
	}
}

void	ft_move_right(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	pa += M_PI_2;
	pa = norm_angle(pa);
	i = (int)(data->p1.x + (cos(pa) * (MOVE_STEP * 3)));
	j = (int)(data->p1.y + (sin(pa) * (MOVE_STEP * 3)));
	if (ft_is_wall(map, i, j))
	{
		data->p1.x += cos(pa) * MOVE_STEP;
		data->p2.x += cos(pa) * MOVE_STEP;
		data->p1.y += sin(pa) * MOVE_STEP;
		data->p2.y += sin(pa) * MOVE_STEP;
	}
}

void	ft_move_left(t_data *data, char **map, double pa)
{
	int	i;
	int	j;

	pa -= M_PI_2;
	pa = norm_angle(pa);
	i = (int)(data->p1.x + (cos(pa) * (MOVE_STEP * 3)));
	j = (int)(data->p1.y + (sin(pa) * (MOVE_STEP * 3)));
	if (ft_is_wall(map, i, j))
	{
		data->p1.x += cos(pa) * MOVE_STEP;
		data->p2.x += cos(pa) * MOVE_STEP;
		data->p1.y += sin(pa) * MOVE_STEP;
		data->p2.y += sin(pa) * MOVE_STEP;
	}
}

void	ft_move(t_data *data)
{
	char	**map;
	double	*pa;

	pa = &data->angle;
	map = data->cub->maps;
	if (data->key_to_move == W_KEY)
		ft_move_up(data, map, data->angle);
	if (data->key_to_move == S_KEY)
		ft_move_down(data, map, data->angle);
	if (data->key_to_move == D_KEY)
		ft_move_right(data, map, data->angle);
	if (data->key_to_move == A_KEY)
		ft_move_left(data, map, data->angle);
}
