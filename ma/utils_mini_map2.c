/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:06:19 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/19 23:19:00 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_mini_map(t_data *data, t_mini_map_2 *mini)
{
	while (mini->j < 200)
	{
		if (mini->p1 < mini->h && mini->p2 <= mini->w)
		{
			if (mini->mini_map[mini->p1][mini->p2] == '1')
				render_rect(&data->img, \
				(t_rect){mini->j, mini->i, 10, 10, RED});
			if (mini->mini_map[mini->p1][mini->p2] == '0')
				render_rect(&data->img, \
				(t_rect){mini->j, mini->i, 10, 10, 0xff0});
			if (mini->mini_map[mini->p1][mini->p2] == 'X')
				render_rect(&data->img, \
				(t_rect){mini->j, mini->i, 10, 10, 0xff0});
			if (mini->mini_map[mini->p1][mini->p2] == 'E')
				render_rect(&data->img, \
				(t_rect){mini->j, mini->i, 10, 10, YELLOW});
		}
		mini->p2++;
		mini->j += 10;
	}
}
