/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:22:48 by matef             #+#    #+#             */
/*   Updated: 2022/11/30 12:39:53 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void DDA(t_data *data, t_point p1, t_point p2)


float norm_angle(float ray_angle)
{
    ray_angle = fmod(ray_angle, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;
    return ray_angle;
}

int ft_is_looking_down(float   angle)
{
    return (0 < angle && angle < M_PI);
}

int ft_is_looking_up(float   angle)
{
    return (!ft_is_looking_down(angle));
}

int ft_is_looking_right(float   angle)
{
    return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int ft_is_looking_left(float   angle)
{
    return !ft_is_looking_right(angle);
}

int fr_horizontale(t_data *data, float ray_angle, t_point *p2)
{
    t_point p1;
    float x_inter;
    float y_inter;
    int x_step;
    int y_step;
    int check = 0;

    p1 = data->p1;
    ray_angle = norm_angle(ray_angle);
    y_inter = floor(p1.y / GRID_SIZE) * GRID_SIZE;
    if (ft_is_looking_down(ray_angle))
        y_inter += GRID_SIZE;
        
    x_inter = p1.x + (y_inter - p1.y) / tan(ray_angle);
    
    y_step = GRID_SIZE;
    if (ft_is_looking_up(ray_angle))
        y_step *= -1;

    x_step = y_step / tan(ray_angle);
    
    if (ft_is_looking_left(ray_angle) && x_step > 0)
        x_step *= -1;
    
    if (ft_is_looking_right(ray_angle) && x_step < 0)
        x_step *= -1;
    
    
    float y_i = y_inter;
    float x_i = x_inter;

    if (ft_is_looking_up(ray_angle))
    {
        // y_i--;
        check = 1;
    }
    while ((0 < x_i && x_i < 31 * 32) && (0 < y_i && y_i < 16 * 32))
    {
        if (!ft_is_wall(data->cub->maps, x_i, y_i - check))
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

int fr_verticale(t_data *data, float ray_angle, t_point *p2)
{
    t_point p1;
    // t_point p2;
    float x_inter;
    float y_inter;
    int x_step;
    int y_step;
    int check = 0;
    p1 = data->p1;
    
    ray_angle = norm_angle(ray_angle);
    x_inter = floor(p1.x / GRID_SIZE) * GRID_SIZE;
    if (ft_is_looking_right(ray_angle))
        x_inter += GRID_SIZE;
    y_inter = p1.y + (x_inter - p1.x) * tan(ray_angle); 
    
    x_step = GRID_SIZE;
    
    if (ft_is_looking_left(ray_angle))
        x_step *= -1;
    
    y_step = x_step * tan(ray_angle);
    
    if (ft_is_looking_up(ray_angle) && y_step > 0)
        y_step *= -1;
    
    if (ft_is_looking_down(ray_angle) && y_step < 0)
        y_step *= -1;
    
    float x_i = x_inter;
    float y_i = y_inter;
    
    if (ft_is_looking_left(ray_angle))
    {
        // x_i--;
        check = 1;
    }
    
    while ((0 < x_i && x_i < 31 * 32) && (0 < y_i && y_i < 16 * 32))
    {
        if (!ft_is_wall(data->cub->maps, x_i - check, y_i))
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

void ft_ray(t_data *data, float ray_angle)
{
    t_point p1;
    t_point p2;
    t_point p3;

    p1 = data->p1;

    int vert = fr_verticale(data, ray_angle, &p2);

    
    int horiz = fr_horizontale(data, ray_angle, &p3);
    // DDA(data, p1, p3);

    float dist_1;
    float dist_2;

    if (vert)
        dist_1 = (float)sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    else
        dist_1 = INT_MAX;

    if (horiz)
        dist_2 = (float)sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));
    else
        dist_2 = INT_MAX;

    if (dist_1 == INT_MAX && dist_2 == INT_MAX)
        return ;

    // printf("dist 1 2 %f %f\n", dist_1, dist_2);

    if (dist_1 < dist_2)
    {
        printf("fr_horizontale %f\n", dist_1);
        if (p2.x == 0 && p2.y == 0)
            printf("yes p2\n");
        DDA(data, p1, p2);
    }
    if (dist_2 < dist_1)
    {
        printf("fr_verticale %f\n", dist_2);
        if (p3.x == 0 && p3.y == 0)
            printf("yes p3\n");
        DDA(data, p1, p3);
    }
}

void ft_cast_rays(t_data *data)
{
    int i;
    float ray_angle;
    // t_point p2;

    i = 0;
    ray_angle = data->angle - (VIEW_ANGLE / 2);
    // ray_angle = data->angle - (VIEW_ANGLE / 2);
    while (i < NBR_RAYS)
    {
        // printf("ray %f\n", ray_angle);
        // if(fr_horizontale(data, ray_angle, &p2))
        //     DDA(data, data->p1, p2);
        // if(fr_verticale(data, ray_angle, &p2))
        //     DDA(data, data->p1, p2);
            // printf("%f %f\n", p2.x, p2.y);

        ft_ray(data, ray_angle);
        ray_angle += VIEW_ANGLE / NBR_RAYS;
        ray_angle = norm_angle(ray_angle);
        i++;
    }
}

