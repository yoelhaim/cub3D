/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:12:39 by matef             #+#    #+#             */
/*   Updated: 2022/12/20 17:22:48 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	DDA(t_data *data, t_point p1, t_point p2)
{
	int		i;
	t_line	line;
	t_img	*img;

	img = &data->img;
	i = 0;
	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
    line.x_inc = line.dx / (double)line.steps;
    line.y_inc = line.dy / (double)line.steps;
    line.x = p1.x;
    line.y = p1.y;
    while (i <= line.steps)
	{
        img_pix_put(img, round(line.x), round(line.y), YELLOW);
        line.x += line.x_inc; 
        line.y += line.y_inc;
		i++;
    }
}
