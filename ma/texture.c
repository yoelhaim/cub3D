/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:59:47 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/09 22:10:44 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void ft_texture(t_data *data)
{
	char	*img;
	int		w, h;
	char *path = "texture/wall.xpm";

	img = mlx_xpm_file_to_image(data->mlx_ptr, path , &w, &h);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 0, 0);
}