/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/20 22:46:09 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + ((y)* data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void next_step(t_cub3d *cubmap, t_mlx  *data_mlx)
{
	printf("=====> %s\n------------------------\n", cubmap->no);
	data_mlx->mlx = mlx_init();
	data_mlx->mlx_win = mlx_new_window(data_mlx->mlx, WIDTH, HEIGHT, "Hello world!");
	data_mlx->img = mlx_new_image(data_mlx->mlx, WIDTH, HEIGHT);
	data_mlx->addr = mlx_get_data_addr(data_mlx->img, &data_mlx->bits_per_pixel, &data_mlx->line_length,&data_mlx->endian);
	int i =0;

	while (i < WIDTH)
	{
		my_mlx_pixel_put(data_mlx, i, 10,  0x00FF0000);
		i++;
	}
	i =0;
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(data_mlx, 10, i,  0x00FF0000);
		i++;
	}
	// int j = i;

	// while (i < HEIGHT)
	// {
	// 	my_mlx_pixel_put(data_mlx, j, i,  0xFFFFF);
	// }
// 	while(i < WIDTH)
// 	{
// 		my_mlx_pixel_put(data_mlx, i, i - 200, 0x00FF0000);
// 		i++;
// 	}
// 	i =0;
// 	while(i < WIDTH)
// 	{
// 		my_mlx_pixel_put(data_mlx, i, 200, 0xFFFF);
// 		i++;
// 	}
// 	i =0;
// 	while(i < WIDTH)
// 	{
// 		my_mlx_pixel_put(data_mlx, i, 600, 0xFFFF);
// 		i++;
// 	}
//  i =0;
// 	while(i < WIDTH)
// 	{
// 		my_mlx_pixel_put(data_mlx, i -89,  300, 0x00FF0000);
// 		i++;
// 	}
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->mlx_win, data_mlx->img, 0, 0);
	mlx_loop(data_mlx->mlx);
}

int main(int ac, char **av)
{
	char *namefile;
	t_cub3d cubmap;
	// t_mlx	mlx;

	// cubmap.no = NULL;
	// cubmap.so = NULL;
	// cubmap.ea = NULL;
	// cubmap.we = NULL;

	if (ac != 2)
		return (printf("arg don't Valid"), 1);
	namefile = av[1];
	if (!check_exten(namefile))
		return (write(1, "error open  map !\n", 19), 1);
	else if (!check_name_exc(namefile))
		return (write(1, "error extention maps !\n", 24), 1);
	else
	{
		if (!read_to_file(namefile, &cubmap))
			return (printf("error check map\n"), 1);
		if (!check_maps(&cubmap, namefile))
			return (printf("error check map 1\n"), 1);
		if (!check_floor_ceil(cubmap.floor) || !check_floor_ceil(cubmap.ciel))
			return (printf("error color\n"), 0);
		if (!check_file_texture(&cubmap) || !check_is_valid_map(cubmap.maps,& cubmap))
			return (printf("error reading map \n"), 0);
		printf("hello to Cub3d! \n");

	printf("=====> %s\n------------------------\n", cubmap.no);
	printf("=====> p-x %d p-y %d\n------------------------\n", cubmap.pos_player_x, cubmap.pos_player_y);
		// next_step(&cubmap, &mlx);
	//  system("leaks Cub3d");
		
	}
	return (0);
}
