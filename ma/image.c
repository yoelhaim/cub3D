/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:57:17 by matef             #+#    #+#             */
/*   Updated: 2022/11/30 22:50:30 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

void create_image(t_data *data)
{
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
    render(data, data->cub->maps);
}


int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

double ft_grid(double x)
{
	return (GRID_SIZE * x);
}

t_rect ft_rect(double j, double i, int color)
{
	return ((t_rect){ft_grid(j), ft_grid(i), ft_grid(1), ft_grid(1), color});
}

t_rect ft_player(double j, double i, int color)
{
	return ((t_rect){ft_grid(j), ft_grid(i), ft_grid(1) / 2, ft_grid(1) / 2, color});
}

t_rect ft_line(double j, double i, int color)
{
	return ((t_rect){ft_grid(j) + GRID_SIZE / 4 - 2, ft_grid(i) - 5, 4, ft_grid(1) / 2 - 1, color});
}

void DDA(t_data *data, t_point p1, t_point p2)
{
	int i;
	t_line line;
	t_img *img;

	img = &data->img;
	i = 0;
	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	
    line.x_inc = line.dx / (double)line.steps;
    line.y_inc = line.dy / (double)line.steps;
	
    line.X = p1.x;
    line.Y = p1.y;
	
    while (i <= line.steps)
	{
        img_pix_put(img, round(line.X), round(line.Y), YELLOW);
        line.X += line.x_inc; 
        line.Y += line.y_inc;
		i++;
    }
}

void DDA2(t_data *data, t_point p1, t_point p2)
{
	int i;
	t_line line;
	t_img *img;
	

	img = &data->img;
	i = 0;
	line.dx = p2.x - p1.x;
	line.dy = p2.y - p1.y;
	
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	
    line.x_inc = line.dx / (double)line.steps;
    line.y_inc = line.dy / (double)line.steps;
	
    line.X = p1.x;
    line.Y = p1.y;
	
    while (i <= line.steps)
	{
        img_pix_put(img, round(line.X), round(line.Y), RED);
        line.X += line.x_inc; 
        line.Y += line.y_inc;
		i++;
    }
}

void ft_get_intersection(t_data *data, t_point *orgin, t_point *p)
{

	double pa = data->angle;

	(void) orgin;
	(void) pa;
	

	printf("%f %f\n", p->x, p->y);
}

void draw_grid(t_data *data)
{
	int i = 0;
	int j;
	
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			img_pix_put(&data->img, i, j, DARK);
			j++;
		}
		i += GRID_SIZE;
	}

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i <  WINDOW_WIDTH)
		{
			img_pix_put(&data->img, i, j, DARK);
			i++;
		}
		j += GRID_SIZE;
	}
}

void draw_map(t_data *data, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				render_rect(&data->img, ft_rect(j, i, WALL));
			else if (map[i][j] == '0')
				render_rect(&data->img, ft_rect(j, i, SPACE));
			j++;
		}
		i++;
	}
}

int	render(t_data *data, char **map)
{
	if (data->win_ptr == NULL)
		return (1);

	draw_map(data, map);
	draw_grid(data);
	
	render_rect(&data->img, (t_rect){data->p1.x, data->p1.y, 5, 5, YELLOW});
	ft_cast_rays(data);
	DDA2(data, data->p1, data->p2);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}
