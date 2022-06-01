/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:15:20 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 14:07:42 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

void	draw_player(t_data *data)
{
	t_square	sq;

	sq.p.x = 0;
	sq.p.y = 0;
	data->player.img = mlx_new_image(data->mlx.mlx, 3, 3);
	data->player.addr = mlx_get_data_addr(data->player.img,
			&data->player.bits,
			&data->player.line_length, &data->player.endian);
	sq.img = &data->player;
	sq.size = 3;
	sq.colour = 0x00CC0066;
	sq.out_colour = 0x00CC0066;
	draw_square(&sq);
}

static void	draw_map_helper(t_square *sq, int value)
{
	if (value == WALL)
	{
		sq->colour = 0xAAB0C4DE;
		sq->out_colour = 0;
		draw_square(sq);
	}
	else if (value == EMPTY)
	{
		sq->colour = 0xAAFFFFFF;
		sq->out_colour = 0xAAFFFFFF;
		draw_square(sq);
	}
	else if (value == DOOR_CLOSED)
	{
		sq->colour = 0xAA00FF00;
		sq->out_colour = 0xAA00FF00;
		draw_square(sq);
	}
	else if (value == SPACE)
	{
		sq->colour = 0xFF000000;
		sq->out_colour = 0xFF000000;
		draw_square(sq);
	}
}

void	draw_map(t_data *data, int i, int j)
{
	t_square	sq;

	data->map.img = mlx_new_image(data->mlx.mlx, data->info.width * MAP_TILE,
			data->info.height * MAP_TILE);
	data->map.addr = mlx_get_data_addr(data->map.img, &data->map.bits,
			&data->map.line_length, &data->map.endian);
	sq.size = MAP_TILE;
	sq.img = &data->map;
	while (++i < data->info.height)
	{
		sq.p.y = i * MAP_TILE;
		j = -1;
		while (++j < data->info.width)
		{
			sq.p.x = j * MAP_TILE;
			draw_map_helper(&sq, data->info.int_map[i][j]);
		}
	}
}
