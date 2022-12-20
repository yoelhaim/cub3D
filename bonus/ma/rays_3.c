/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:43:16 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 22:19:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	ft_horiz_1(t_data *data, t_inter inter, double ray_angle, t_point *p2)
{
	double	y_i;
	double	x_i;

	y_i = inter.y_inter;
	x_i = inter.x_inter;
	while ((0 <= x_i && x_i <= data->x11 * 32) && \
	(0 <= y_i && y_i <= data->y11 * 32))
	{
		if (!ft_is_wall(data->cub->maps, x_i, y_i - \
		ft_is_looking_up(ray_angle)))
		{
			p2->x = x_i;
			p2->y = y_i;
			return (1);
		}
		x_i += inter.x_step;
		y_i += inter.y_step;
	}
	return (0);
}

int	fr_horizontale(t_data *data, double ray_angle, t_point *p2)
{
	t_point	player;
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	player = data->p1;
	y_inter = floor(player.y / GRID_SIZE) * GRID_SIZE;
	if (ft_is_looking_down(ray_angle))
		y_inter += GRID_SIZE;
	x_inter = player.x + ((y_inter - player.y) / tan(ray_angle));
	y_step = GRID_SIZE;
	if (ft_is_looking_up(ray_angle))
		y_step *= -1;
	x_step = GRID_SIZE / tan(ray_angle);
	if (ft_is_looking_left(ray_angle) && x_step > 0)
		x_step *= -1;
	if (ft_is_looking_right(ray_angle) && x_step < 0)
		x_step *= -1;
	return (ft_horiz_1(data, (t_inter){x_inter, y_inter, x_step, y_step}, \
	ray_angle, p2));
}

int	ft_verti_1(t_data *data, t_inter inter, double ray_angle, t_point *p2)
{
	double	x_i;
	double	y_i;

	x_i = inter.x_inter;
	y_i = inter.y_inter;
	while ((0 <= x_i && x_i <= data->x11 * 32) && \
	(0 <= y_i && y_i <= data->y11 * 32))
	{
		if (!ft_is_wall(data->cub->maps, x_i - \
		ft_is_looking_left(ray_angle), y_i))
		{
			p2->x = x_i;
			p2->y = y_i;
			return (1);
		}
		x_i += inter.x_step;
		y_i += inter.y_step;
	}
	return (0);
}

int	fr_verticale(t_data *data, double ray_angle, t_point *p2)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	x_inter = floor(data->p1.x / GRID_SIZE) * GRID_SIZE;
	if (ft_is_looking_right(ray_angle))
		x_inter += GRID_SIZE;
	y_inter = data->p1.y + ((x_inter - data->p1.x) * tan(ray_angle));
	x_step = GRID_SIZE;
	if (ft_is_looking_left(ray_angle))
		x_step *= -1;
	y_step = GRID_SIZE * tan(ray_angle);
	if (ft_is_looking_up(ray_angle) && y_step > 0)
		y_step *= -1;
	if (ft_is_looking_down(ray_angle) && y_step < 0)
		y_step *= -1;
	return (ft_verti_1(data, (t_inter){x_inter, y_inter, x_step, y_step}, \
	ray_angle, p2));
}

double	ft_calc_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
