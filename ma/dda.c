/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:12:39 by matef             #+#    #+#             */
/*   Updated: 2022/12/05 20:13:30 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void DDA(t_data *data, t_point p1, t_point p2)
{
	int i;
	t_line line;
	t_img *img;

	img = &data->img;
	i = 0;
	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	
    line.x_inc = line.dx / (double)line.steps;
    line.y_inc = line.dy / (double)line.steps;
	
    line.X = p1.x;
    line.Y = p1.y;
	
    while (i <= line.steps)
	{
        img_pix_put(img, round(line.X), round(line.Y), YELLOW);
        line.X += line.x_inc; 
        line.Y += line.y_inc;
		i++;
    }
}
