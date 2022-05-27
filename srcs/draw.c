/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:46:09 by sclam             #+#    #+#             */
/*   Updated: 2022/05/25 21:59:00 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_img *img, int size, int colour, int out_colour, t_point p)
{
	int	i;
	int	j;

	i = p.y;
	while (i < p.y + size)
	{
		j = p.x;
		while (j < p.x + size)
		{
			if (i == 0 || i == p.y + size - 1 || j == 0 || j == p.x + size - 1)
				my_mlx_pixel_put(img, j++, i, out_colour);
			else
				my_mlx_pixel_put(img, j++, i, colour);
		}
		++i;
	}
}

void	draw_line(t_img *img, int colour, t_point f, t_point t)
{
	double	x;
	double	y;
	double	max;
	double	n;

	x = t.x - f.x;
	y = t.y - f.y;
	max = fmax(fabs(x), fabs(y));
	x /= max;
	y /= max;
	n = 0;
	while (n < max)
	{
		my_mlx_pixel_put(img, f.x, f.y, colour);
		f.x += x;
		f.y += y;
		++n;
	}
}

void	draw_player(t_data *data)
{
	t_point	p;

	p.x = 0;
	p.y = 0;
	data->player.img = mlx_new_image(data->mlx.mlx, 3, 3);
	data->player.addr = mlx_get_data_addr(data->player.img, &data->player.bits_per_pixel, &data->player.line_length, &data->player.endian);
	draw_square(&data->player, 3, 0x00CC0066, 0x00CC0066, p);
}

void	draw_map(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	i = 0;
	data->map.img = mlx_new_image(data->mlx.mlx, data->info.width * MAP_TILE, data->info.height * MAP_TILE);
	data->map.addr = mlx_get_data_addr(data->map.img, &data->map.bits_per_pixel, &data->map.line_length, &data->map.endian);
	while (i < data->info.height)
	{
		p.y = i * MAP_TILE;
		j = 0;
		while (j < data->info.width)
		{
			p.x = j * MAP_TILE;
			if (data->info.int_map[i][j] == WALL)
				draw_square(&data->map, MAP_TILE, 0xAAB0C4DE, 0x00000000, p);
			// else if (data->info.int_map[i][j] == PLAYER || data->info.int_map[i][j] == EMPTY)
			else if (data->info.int_map[i][j] == EMPTY)
				draw_square(&data->map, MAP_TILE, 0xAAFFFFFF, 0xAAFFFFFF, p);
			else if (data->info.int_map[i][j] == DOOR_CLOSED)
				draw_square(&data->map, MAP_TILE, 0xAA00FF00, 0xAA00FF00, p);
			// else if (data->info.int_map[i][j] == DOOR_CLOSED)
			// 	draw_square(&data->map, MAP_TILE, 0xAAFF00FF, 0xAAFF00FF, p);
			else if (data->info.int_map[i][j] == SPACE)
				draw_square(&data->map, MAP_TILE, 0xFF000000, 0xFF000000, p);
			++j;
		}
		++i;
	}
}
