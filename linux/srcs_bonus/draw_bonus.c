/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:46:09 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:36:40 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

void	draw_player(t_data *data)
{
	t_point	p;

	p.x = 0;
	p.y = 0;
	data->player.img = mlx_new_image(data->mlx.mlx, 3, 3);
	data->player.addr = mlx_get_data_addr(data->player.img,
			&data->player.bits,
			&data->player.line_length, &data->player.endian);
	draw_square(&data->player, 3, 0x00CC0066, 0x00CC0066, p);
}

void	draw_map(t_data *data, int i, int j)
{
	t_point	p;

	data->map.img = mlx_new_image(data->mlx.mlx, data->info.width * MAP_TILE,
			data->info.height * MAP_TILE);
	data->map.addr = mlx_get_data_addr(data->map.img, &data->map.bits,
			&data->map.line_length, &data->map.endian);
	while (++i < data->info.height)
	{
		p.y = i * MAP_TILE;
		j = -1;
		while (++j < data->info.width)
		{
			p.x = j * MAP_TILE;
			if (data->info.int_map[i][j] == WALL)
				draw_square(&data->map, MAP_TILE, 0xAAB0C4DE, 0x00000000, p);
			else if (data->info.int_map[i][j] == EMPTY)
				draw_square(&data->map, MAP_TILE, 0xAAFFFFFF, 0xAAFFFFFF, p);
			else if (data->info.int_map[i][j] == DOOR_CLOSED)
				draw_square(&data->map, MAP_TILE, 0xAA00FF00, 0xAA00FF00, p);
			else if (data->info.int_map[i][j] == SPACE)
				draw_square(&data->map, MAP_TILE, 0xFF000000, 0xFF000000, p);
		}
	}
}

void	draw_fc(t_data *data)
{
	int	y;
	int	x;
	int	is_floor;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2 + data->rays.pitch)
			is_floor = 1;
		else
			is_floor = 0;
		while (x < WIDTH)
		{
			if (is_floor)
				my_mlx_pixel_put(&data->img, x, y, data->info.f->trgb);
			else
				my_mlx_pixel_put(&data->img, x, y, data->info.c->trgb);
			x++;
		}
		y++;
	}
}

int	shade_color(int color, t_dda *dda)
{
	if ((dda->side == 1 && dda->raydiry >= 0)
		|| (dda->side == 0 && dda->raydirx >= 0))
		color = (color >> 1) & 8355711;
	return (color);
}

void	draw_loop(t_data *data, t_dda *dda, int x)
{
	int	y;
	int	color;
	int	texy;

	y = dda->drawstart - 1;
	while (++y < dda->drawend)
	{
		texy = (int)dda->texpos & (TEX - 1);
		if (dda->hit == 2 && texy == 0)
			texy = 1;
		dda->texpos += dda->step;
		if (dda->side == 1 && dda->raydiry < 0 && dda->hit == 1)
			color = get_tex_colour(data->info.so, dda->texx, texy);
		else if (dda->side == 1 && dda->raydiry >= 0 && dda->hit == 1)
			color = get_tex_colour(data->info.no, dda->texx, texy);
		else if (dda->side == 0 && dda->raydirx >= 0 && dda->hit == 1)
			color = get_tex_colour(data->info.ea, dda->texx, texy);
		else if (dda->side == 0 && dda->raydirx < 0 && dda->hit == 1)
			color = get_tex_colour(data->info.we, dda->texx, texy);
		else if (dda->hit == 2)
			color = get_tex_colour(data->info.dr, dda->texx, texy);
		else
			color = get_tex_colour(data->info.dr_wall, dda->texx, texy);
		my_mlx_pixel_put(&data->img, x, y, shade_color(color, dda));
	}
}
