/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pro <pro@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:55:50 by pro               #+#    #+#             */
/*   Updated: 2022/11/19 20:42:18 by pro              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"



int main(int ac, char **av)
{
	char	*namefile;
	t_cub3d cubmap;

	if (ac != 2)
		return (printf("arg don't Valid"), 1);
	namefile = av[1];
	if (!check_exten(namefile))
		return (write(1, "error open  map !\n", 19), 1);
	else if (!check_name_exc(namefile))
		return (write(1, "error extention maps !\n", 24), 1);
	else
	{
		if (!read_to_file(namefile, &cubmap) )
			return(printf("error check map\n"),1);
        check_maps(&cubmap);
        // if (!check_floor_ceil(cubmap.floor) || !check_floor_ceil(cubmap.ciel))
        //     return (printf("error color\n"), 0);
        // if(!check_file_texture(&cubmap))
        //     return (printf("error textur\n"), 0);
        printf("%d\n", check_is_valid_map(cubmap.maps));
		printf("Go! %s\n", cubmap.so);
		printf("Go! %s\n", cubmap.no);
		printf("Go! %s\n", cubmap.we);
		printf("Go! %s\n", cubmap.ea);
		printf("Go fllo! %d\n", cubmap.floor[0]);
		printf("Go fllo! %d\n", cubmap.floor[1]);
		printf("Go fllo! %d\n", cubmap.floor[2]);
		printf("index ! %d\n", cubmap.last_index);
	}
}
