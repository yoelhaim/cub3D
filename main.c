
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
    // return (1);
	ft_init(&data, &cubmap);
	ft_main(&data);
	ft_end(data);
	return (0);
}