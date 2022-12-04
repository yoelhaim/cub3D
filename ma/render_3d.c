/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:51:05 by matef             #+#    #+#             */
/*   Updated: 2022/12/04 14:48:53 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	ft_render3d(t_data *data, double ray_dist, int index_of_ray, int hor)
{
    double	proj;
	double	wall_stripe;

    proj = WINDOW_WIDTH / 2 + (tan(VIEW_ANGLE / 2));
    wall_stripe = (GRID_SIZE / ray_dist) * proj;
    if (hor)
        render_rect(&data->img, (t_rect){index_of_ray, (WINDOW_HEIGHT / 2) - (wall_stripe / 2), 1, wall_stripe, YELLOW});
    else
        render_rect(&data->img, (t_rect){index_of_ray, (WINDOW_HEIGHT / 2) - (wall_stripe / 2), 1, wall_stripe, RED});
        
}