/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:00:20 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/20 22:19:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

double	norm_angle(double ray_angle)
{
	ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	return (ray_angle);
}

int	ft_is_looking_down(double angle)
{
	return (0 < angle && angle < M_PI);
}

int	ft_is_looking_up(double angle)
{
	return (!ft_is_looking_down(angle));
}

int	ft_is_looking_right(double angle)
{
	return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int	ft_is_looking_left(double angle)
{
	return (!ft_is_looking_right(angle));
}
