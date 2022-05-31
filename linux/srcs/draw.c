/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:40:42 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 13:58:04 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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
		dda->texpos += dda->step;
		if (dda->side == 1 && dda->raydiry < 0)
			color = get_tex_colour(data->info.so, dda->texx, texy);
		else if (dda->side == 1 && dda->raydiry >= 0)
			color = get_tex_colour(data->info.no, dda->texx, texy);
		else if (dda->side == 0 && dda->raydirx >= 0)
			color = get_tex_colour(data->info.ea, dda->texx, texy);
		else if (dda->side == 0 && dda->raydirx < 0)
			color = get_tex_colour(data->info.we, dda->texx, texy);
		my_mlx_pixel_put(&data->img, x, y, shade_color(color, dda));
	}
}
