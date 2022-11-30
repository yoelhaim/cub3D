/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:22:48 by matef             #+#    #+#             */
/*   Updated: 2022/12/01 00:12:10 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void DDA(t_data *data, t_point p1, t_point p2)


double norm_angle(double ray_angle)
{
    ray_angle = fmod(ray_angle, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;
    return ray_angle;
}

int ft_is_looking_down(double   angle)
{
    return (0 < angle && angle < M_PI);
}

int ft_is_looking_up(double   angle)
{
    return (!ft_is_looking_down(angle));
}

int ft_is_looking_right(double   angle)
{
    return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int ft_is_looking_left(double   angle)
{
    return !ft_is_looking_right(angle);
}

int fr_horizontale(t_data *data, double ray_angle, t_point *p2)
{
    t_point p1;
    double x_inter;
    double y_inter;
    double x_step;
    double y_step;

    p1 = data->p1;
    
    // ray_angle = norm_angle(ray_angle);
    y_inter = floor(p1.y / GRID_SIZE) * GRID_SIZE;
    
    if (ft_is_looking_down(ray_angle))
        y_inter += GRID_SIZE;
        
    x_inter = p1.x + ((y_inter - p1.y) / tan(ray_angle));
    
    y_step = GRID_SIZE;
    if (ft_is_looking_up(ray_angle))
        y_step *= -1;

    x_step = GRID_SIZE / tan(ray_angle);
    
    if (ft_is_looking_left(ray_angle) && x_step > 0)
        x_step *= -1;
    
    if (ft_is_looking_right(ray_angle) && x_step < 0)
        x_step *= -1;
    
    
    double y_i = y_inter;
    double x_i = x_inter;
    while ((0 <= x_i && x_i <= 31 * 32) && (0 <= y_i && y_i <= 16 * 32))
    {
        if (!ft_is_wall(data->cub->maps, x_i, y_i - ft_is_looking_up(ray_angle)))
        {
            p2->x = x_i;
            p2->y = y_i;
            return 1;
        }
        x_i += x_step;
        y_i += y_step;
    }
    return 0;
}

int fr_verticale(t_data *data, double ray_angle, t_point *p2)
{
    double x_inter;
    double y_inter;
    double x_step;
    double y_step;

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
    
    double x_i = x_inter;
    double y_i = y_inter;
    
    while ((0 <= x_i && x_i <= 31 * 32) && (0 <= y_i && y_i <= 16 * 32))
    {
        if (!ft_is_wall(data->cub->maps, x_i - ft_is_looking_left(ray_angle), y_i))
        {
            p2->x = x_i;
            p2->y = y_i;
            return (1);    
        }
        x_i += x_step;
        y_i += y_step;
    }
    return 0;
}

double ft_calc_distance(t_point p1, t_point p2)
{
    return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

double get_verticale_ray(t_data *data, double ray_angle, t_point *p)
{
    if (fr_verticale(data, ray_angle, p))
        return (ft_calc_distance(data->p1, *p));
    return (INT_MAX);
}

double get_horizontale_ray(t_data *data, double ray_angle, t_point *p)
{
    if (fr_horizontale(data, ray_angle, p))
        return (ft_calc_distance(data->p1, *p));
    return (INT_MAX);
}

void ft_ray(t_data *data, double ray_angle)
{
    t_point p1;
    t_point p2;
    double dist_1;
    double dist_2;

    dist_1 = get_horizontale_ray(data, ray_angle, &p1);
    dist_2 = get_verticale_ray(data, ray_angle, &p2);
    if (dist_1 < dist_2)
        DDA(data, data->p1, p1);
    else if (dist_2 < dist_1)
        DDA(data, data->p1, p2);
}

void ft_cast_rays(t_data *data)
{
    int		i;
    double	ray_angle;

    i = 0;
    ray_angle = data->angle - (VIEW_ANGLE / 2);
    while (i < NBR_RAYS)
    {
        ft_ray(data, ray_angle);
        ray_angle += VIEW_ANGLE / NBR_RAYS;
        ray_angle = norm_angle(ray_angle);
        i++;
    }
}

