/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:47 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/08 18:21:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void ft_texture(t_data *data)
{
	void	*img;
	int w, h;
	char *path = "/Users/yoelhaim/42/Cub3d/texture/planks.xpm";

	img = mlx_xpm_file_to_image(data->mlx_ptr, path , &w, &h);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 0, 0);
}