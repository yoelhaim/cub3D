/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/12/20 23:03:28 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	ft_end(t_data	data)
{
	mlx_hook(data.win_ptr, 2, 0, ft_event, &data);
	mlx_hook(data.win_ptr, 3, 0, ft_test, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_esc, &data);
	mlx_loop_hook(data.mlx_ptr, render_next_frame, &data);
	mlx_loop(data.mlx_ptr);
}

double	ft_init_direction(char direction)
{
	if (direction == 'E')
		return (0);
	else if (direction == 'N')
		return (1.5 * M_PI);
	else if (direction == 'S')
		return (M_PI_2);
	return (M_PI);
}

void	*get_texture_img(void *mlx_ptr, char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx_ptr, path, &w, &h);
	if (!img)
		exit(0);
	return (img);
}

unsigned int	*ft_get_data_addr(void *img)
{
	int				bpp;
	int				len;
	int				end;
	unsigned int	*addr;

	addr = (unsigned int *)mlx_get_data_addr(img, &bpp, &len, &end);
	if (!addr)
		exit(1);
	return (addr);
}

void	get_texture_adrr(t_data *data, t_cub3d *cubmap)
{
	void	*img;
	void	*img2;
	void	*img3;
	void	*img4;

	img = get_texture_img(data->mlx_ptr, cubmap->so);
	data->so = ft_get_data_addr(img);
	img2 = get_texture_img(data->mlx_ptr, cubmap->ea);
	data->ea = ft_get_data_addr(img2);
	img3 = get_texture_img(data->mlx_ptr, cubmap->no);
	data->no = ft_get_data_addr(img3);
	img4 = get_texture_img(data->mlx_ptr, cubmap->we);
	data->we = ft_get_data_addr(img4);
}
