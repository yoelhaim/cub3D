/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:25:28 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/18 21:55:03 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

char *add_square_map(char *map, int long_width)
{
	int		len;
	char	*tmp;
	int		i;

	len = ft_strlen(map);
	tmp = calloc(long_width + 1, sizeof(char));
	i = 0;
	while (map[i])
	{
		tmp[i] = map[i];
		i++;
	}
	while (i < long_width)
		tmp[i++] = 'x';
	free(map);
	return (tmp);
}

void	convert_map(t_cub3d *cubmap)
{
	int	i;
	
	i = 0;
	while (cubmap->maps[i])
	{
		cubmap->maps[i] = add_square_map(cubmap->maps[i], cubmap->width_of_map);
		i++;
	}
	
}


int ft_parsing(int ac, char *file_name, t_cub3d *cubmap)
{
	if (ac != 2)
		return (ft_putstr_fd("Argument not valid\n", 2), 1);

	if (!check_exten(file_name) || (!check_name_exc(file_name)))
		return (ft_putstr_fd("error: open map!\n", 2), 1);
	
	if (!read_file(file_name, cubmap))
		return (ft_putstr_fd("error check map\n", 2), 1);
	if (!check_floor_ceil(cubmap->floor) || !check_floor_ceil(cubmap->ciel))
		return (ft_putstr_fd("error color\n", 2), 1);
	if (!check_file_texture(cubmap) \
	    || !check_map_is_valid(cubmap))
		return (ft_putstr_fd("error reading map \n", 2), 1);

	cubmap->height_of_map = ft_len_ptr(cubmap->maps);
	convert_map(cubmap);
    return (0);
}


int	main(int ac, char **av)
{
    t_cub3d cubmap;
    t_data data;

    if (ft_parsing(ac, av[1], &cubmap))
        return (1);
	// 	while(1);
	// return 1;
	x11 = cubmap.width_of_map;
	y11 = cubmap.height_of_map;
	ft_init(&data, &cubmap);


	int		w, h;
	void *img;
	void *img2;
	void *img3;
	void *img4;
	int bpp,len,end;


	img = mlx_xpm_file_to_image(data.mlx_ptr, cubmap.so, &w, &h);
	if (!img)
		exit(0);
	data.so = (unsigned int *)mlx_get_data_addr(img, &bpp, &len, &end);
	if (!data.no)
		exit(0);


	img2 = mlx_xpm_file_to_image(data.mlx_ptr, cubmap.ea, &w, &h);
	if (!img2)
		exit(0);
	data.ea = (unsigned int *)mlx_get_data_addr(img2, &bpp, &len, &end);
	if (!data.ea)
		exit(0);


	img3 = mlx_xpm_file_to_image(data.mlx_ptr, cubmap.no, &w, &h);
	if (!img3)
		exit(0);
	data.no = (unsigned int *)mlx_get_data_addr(img3, &bpp, &len, &end);
	if (!data.no)
		exit(1);

	img4 = mlx_xpm_file_to_image(data.mlx_ptr, cubmap.we, &w, &h);
	if (!img4)
		exit(0);
	data.we = (unsigned int *)mlx_get_data_addr(img4, &bpp, &len, &end);
	if (!data.we)
		exit(1);
	ft_main(&data);
	ft_end(data);
	return (0);
}