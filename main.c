
#include "./include/cub3d.h"

int ft_parsing(int ac, char *file_name, t_cub3d *cubmap)
{
	if (ac != 2)
		return (ft_putstr_fd("Argument not valid\n", 2), 1);
	if (!check_exten(file_name) || (!check_name_exc(file_name)))
		return (ft_putstr_fd("error: open map!\n", 2), 1);
	if (!read_to_file(file_name, cubmap))
		return (ft_putstr_fd("error check map\n", 2), 1);
	if (!check_floor_ceil(cubmap->floor) || !check_floor_ceil(cubmap->ciel))
		return (ft_putstr_fd("error color\n", 2), 1);
	if (!check_file_texture(cubmap) \
	    || !check_map_is_valid(cubmap))
		return (ft_putstr_fd("error reading map \n", 2), 1);
	cubmap->length_to_map = ft_len_ptr(cubmap->maps);
    return (0);
}

int	main(int ac, char **av)
{
    t_cub3d cubmap;
    t_data data;

    if (ft_parsing(ac, av[1], &cubmap))
        return (1);

	// char *path = "./gif/14.xpm";
	// int w, h;

	x11 = cubmap.length_width;
	y11 = cubmap.length_to_map;
	ft_init(&data, &cubmap);
	
	// void *img = mlx_xpm_file_to_image(data.mlx_ptr, path, &w, &h);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, 0, 0);
	//mlx_loop(data.mlx_ptr);

	ft_main(&data);
	ft_end(data);
	return (0);
}