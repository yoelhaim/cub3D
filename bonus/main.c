/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:25:28 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/12/23 15:45:07 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d_bonus.h"

void	ft_init(t_data	*data, t_cub3d *cubmap)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	data->cub = cubmap;
	data->angle = ft_init_direction(cubmap->direction);
	data->p1.x = (cubmap->pos_player_x * GRID_SIZE) + (GRID_SIZE / 2);
	data->p1.y = (cubmap->pos_player_y * GRID_SIZE) + (GRID_SIZE / 2);
	data->p2.x = (cubmap->pos_player_x * GRID_SIZE) + (cos(data->angle) * 20);
	data->p2.y = (cubmap->pos_player_y * GRID_SIZE) + (sin(data->angle) * 20);
	data->key_press = -1;
	data->key_to_move = -1;
	data->key_to_move_left = -1;
	data->key_to_oriented = -1;
	get_texture_adrr(data, cubmap);
}

char	*add_square_map(char *map, int long_width)
{
	int		len;
	char	*tmp;
	int		i;

	len = ft_strlen(map);
	tmp = ft_calloc(long_width + 1, sizeof(char));
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

int	ft_parsing(int ac, char *file_name, t_cub3d *cubmap)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\nArgument not valid ❌\n", 2), 1);
	if (!check_exten(file_name) || (!check_name_exc(file_name)))
		return (ft_putstr_fd("Error\nopen map! ❌\n", 2), 1);
	if (!read_file(file_name, cubmap) || \
			!check_floor_ceil(cubmap->floor) || !check_floor_ceil(cubmap->ciel))
		exit(1);
	if (!check_file_texture(cubmap) \
			|| !check_map_is_valid(cubmap))
		exit (1);
	cubmap->height_of_map = ft_len_ptr(cubmap->maps);
	convert_map(cubmap);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cubmap;
	t_data	data;

	if (ft_parsing(ac, av[1], &cubmap))
		return (1);
	data.x11 = cubmap.width_of_map;
	data.y11 = cubmap.height_of_map;
	ft_init(&data, &cubmap);
	create_image(&data);
	ft_end(data);
	return (0);
}
