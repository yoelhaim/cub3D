/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/22 10:33:36 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int ac, char **av)
{
	char	*namefile;
	t_cub3d	cubmap;
	// t_mlx	mlx;

	if (ac != 2)
		return (printf("arg don't Valid"), 1);
	namefile = av[1];
	if (!check_exten(namefile) || (!check_name_exc(namefile)))
		return (write(1, "error open  map !\n", 19), 1);
	if (!read_to_file(namefile, &cubmap) || !check_maps(&cubmap, namefile))
		return (printf("error check map\n"), 1);
	if (!check_floor_ceil(cubmap.floor) || !check_floor_ceil(cubmap.ciel))
		return (printf("error color\n"), 0);
	if (!check_file_texture(&cubmap) \
	|| !check_is_valid_map(cubmap.maps, &cubmap))
		return (printf("error reading map \n"), 0);
	printf("hello to Cub3d! \n");
	printf("==> p-x %d p-y %d\n", cubmap.pos_player_x, cubmap.pos_player_y);
		// next_step(&cubmap, &mlx);
	//  system("leaks Cub3d");
	return (0);
}
