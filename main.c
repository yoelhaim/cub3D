
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
	cubmap->height_of_map = ft_len_ptr(cubmap->maps);
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

	x11 = cubmap.width_of_map;
	y11 = cubmap.height_of_map;
	ft_init(&data, &cubmap);
	
	// void *img = mlx_xpm_file_to_image(data.mlx_ptr, path, &w, &h);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, 0, 0);
	// mlx_loop(data.mlx_ptr);


	/// empty  map   no map

	//printf("%s\n", cu)

	int		w, h;
	// char *path = "texture/so.xpm";
	// char *path2 = "texture/ea.xpm";
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
	


	//printf("mouse %d\n", data.mouse_presed);

	ft_main(&data);

	ft_end(data);
	return (0);
}