/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:12:39 by matef             #+#    #+#             */
/*   Updated: 2022/12/22 19:40:46 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	dda(t_data *data, t_point p1, t_point p2)
{
	int		i;
	t_line	line;
	t_img	*img;

	img = &data->img;
	i = 0;
	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	if (abs(line.dx) > abs(line.dy))
		line.steps = abs(line.dx);
	else
		line.steps = abs(line.dy);
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

int	ft_event(int keycode, t_data *data)
{
	double	x;
	double	y;

	x = data->cub->pos_player_x;
	y = data->cub->pos_player_y;
	if (keycode == ESC)
		ft_esc(data);
	ft_handle_move_event(data, keycode);
	ft_handle_oriented_event(data, keycode);
	ft_handle_move_r_l(data, keycode);
	return (0);
}
