
#include "./include/cub3d.h"

int ft_parsing(int ac, char *file_name, t_cub3d *cubmap)
{
    // return 0;
	if (ac != 2)
		return (ft_putstr_fd("Argument not valid\n", 2), 1);
	if (!check_exten(file_name) || (!check_name_exc(file_name)))
		return (ft_putstr_fd("error :  open  map !\n", 2), 1);
	if (!read_to_file(file_name, cubmap) || !check_maps(cubmap, file_name))
		return (ft_putstr_fd("error check map\n", 2), 1);
	if (!check_floor_ceil(cubmap->floor) || !check_floor_ceil(cubmap->ciel))
		return (ft_putstr_fd("error color\n", 2), 1);
	if (!check_file_texture(cubmap) \
	    || !check_is_valid_map(cubmap->maps, cubmap))
		return (ft_putstr_fd("error reading map \n", 2), 1);
	cubmap->length_to_map = ft_len_ptr(cubmap->maps);
    return (0);
}

void ft_putline(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			printf(".");
		else
			printf("%c", line[i]);
		i++;
	}
}

void print_map(char *map_src)
{
    int		fd;
    char	*line;

    fd = open(map_src, O_RDONLY);


	if (fd < 0)
		return ;
	
	line = get_next_line(fd);
	while (line)
	{
		ft_putline(line);
		line = get_next_line(fd);
	}

}

int	main(int ac, char **av)
{
    t_cub3d cubmap;
    t_data data;

    if (ft_parsing(ac, av[1], &cubmap))
        return 1;
	ft_init(&data, &cubmap);
	
	ft_main(&data);
	ft_end(data);
	return (0);
}