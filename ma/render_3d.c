/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:51:05 by matef             #+#    #+#             */
/*   Updated: 2022/12/14 14:33:26 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int render_texture(t_data *data, t_rect rect, t_ray *ray)
{
	int	i;
    
	i = rect.y;

    int offset_x;
    int offset_y;
    
    if (ray->hit_horizontale)
        offset_x = (int)ray->hit_point->x % GRID_SIZE;
    else
        offset_x = (int)ray->hit_point->y % GRID_SIZE;
    
    // offset_x = 
	while (i < rect.y + rect.height)
	{

        offset_y = (i - rect.y) * ((float)GRID_SIZE / rect.height);
        
        if (ray->hit_horizontale)
            img_pix_put(&data->img, rect.x, i, data->adr[(offset_y * GRID_SIZE) + offset_x]);
        else
            img_pix_put(&data->img, rect.x, i, data->adr2[(offset_y * GRID_SIZE) + offset_x]);
            

		++i;
	}
	return (0);
}

void	ft_render3d(t_data *data, double ray_dist, int index_of_ray, t_ray *ray)
{
    double	proj;
	double	wall_stripe;
    
    proj = WINDOW_WIDTH / 2 + (tan(VIEW_ANGLE / 2));
    wall_stripe = (GRID_SIZE / ray_dist) * proj;
    // if (ray->hit_horizontale)
    // {
        
        render_texture(data, (t_rect){index_of_ray, (WINDOW_HEIGHT / 2) - (wall_stripe / 2), 1, wall_stripe, YELLOW}, ray);
    // }
    // else
    // {
        
    //     render_texture(data, (t_rect){index_of_ray, (WINDOW_HEIGHT / 2) - (wall_stripe / 2), 1, wall_stripe, RED}, ray);
    // }
}
