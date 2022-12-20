/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:22:48 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 22:19:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
