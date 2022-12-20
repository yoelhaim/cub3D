/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:22:48 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 19:46:42 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	fr_horizontale(t_data *data, double ray_angle, t_point *p2)
{
	t_point	player;
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	double	y_i;
	double	x_i;

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
	y_i = y_inter;
	x_i = x_inter;
	while ((0 <= x_i && x_i <= x11 * 32) && (0 <= y_i && y_i <= y11 * 32))
	{
		if (!ft_is_wall(data->cub->maps, x_i, y_i - \
		ft_is_looking_up(ray_angle)))
		{
			p2->x = x_i;
			p2->y = y_i;
			return (1);
		}
		x_i += x_step;
		y_i += y_step;
	}
	return (0);
}

int	fr_verticale(t_data *data, double ray_angle, t_point *p2)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;
	double	x_i;
	double	y_i;

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
	x_i = x_inter;
	y_i = y_inter;
	while ((0 <= x_i && x_i <= x11 * 32) && (0 <= y_i && y_i <= y11 * 32))
	{
		if (!ft_is_wall(data->cub->maps, x_i - \
		ft_is_looking_left(ray_angle), y_i))
		{
			p2->x = x_i;
			p2->y = y_i;
			return (1);
		}
		x_i += x_step;
		y_i += y_step;
	}
	return (0);
}

double	ft_calc_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

double	get_verticale_ray(t_data *data, double ray_angle, t_point *p)
{
	if (fr_verticale(data, ray_angle, p))
		return (ft_calc_distance(data->p1, *p));
	return (INT_MAX);
}

double	get_horizontale_ray(t_data *data, double ray_angle, t_point *p)
{
	if (fr_horizontale(data, ray_angle, p))
		return (ft_calc_distance(data->p1, *p));
	return (INT_MAX);
}

void	ft_ray(t_data *data, double ray_angle, int index_of_ray)
{
	t_point	p1;
	t_point	p2;
	double	dist_1;
	double	dist_2;
	t_ray	ray;

	dist_1 = get_horizontale_ray(data, ray_angle, &p1);
	dist_2 = get_verticale_ray(data, ray_angle, &p2);
	ray.ray_angle = ray_angle;
	if (dist_1 < dist_2)
	{
		ray.hit_horizontale = 1;
		ray.hit_point = &p1;
		dist_1 = dist_1 * cos(ray_angle - data->angle);
		ft_render3d(data, dist_1, index_of_ray, &ray);
	}
	else if (dist_2 < dist_1)
	{
		ray.hit_horizontale = 0;
		ray.hit_point = &p2;
		dist_2 = dist_2 * cos(ray_angle - data->angle);
		ft_render3d(data, dist_2, index_of_ray, &ray);
	}
}

void	ft_cast_rays(t_data *data)
{
	int		i;
	double	ray_angle;

	i = 0;
	ray_angle = data->angle - (VIEW_ANGLE / 2);
	while (i < NBR_RAYS)
	{
		ft_ray(data, ray_angle, i);
		ray_angle += VIEW_ANGLE / NBR_RAYS;
		ray_angle = norm_angle(ray_angle);
		i++;
	}
}
