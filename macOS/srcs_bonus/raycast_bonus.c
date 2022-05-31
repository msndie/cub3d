/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:40:07 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:37:09 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static void	ray_direction(t_data *data, t_dda *dda)
{
	dda->raydirx = data->rays.dir_x + data->rays.plane_x * dda->camerax;
	dda->raydiry = data->rays.dir_y + data->rays.plane_y * dda->camerax;
	dda->deltadistx = fabs(1 / dda->raydirx);
	dda->deltadisty = fabs(1 / dda->raydiry);
	if (dda->raydirx < 0)
	{
		dda->stepx = -1;
		dda->sidedistx = (data->p.x - dda->mapx) * dda->deltadistx;
	}
	else
	{
		dda->stepx = 1;
		dda->sidedistx = (dda->mapx + 1.0 - data->p.x) * dda->deltadistx;
	}
	if (dda->raydiry < 0)
	{
		dda->stepy = -1;
		dda->sidedisty = (data->p.y - dda->mapy) * dda->deltadisty;
	}
	else
	{
		dda->stepy = 1;
		dda->sidedisty = (dda->mapy + 1.0 - data->p.y) * dda->deltadisty;
	}
}

static void	get_side(t_dda *dda)
{
	if (dda->sidedistx < dda->sidedisty)
	{
		dda->sidedistx += dda->deltadistx;
		dda->mapx += dda->stepx;
		dda->side = 0;
	}
	else
	{
		dda->sidedisty += dda->deltadisty;
		dda->mapy += dda->stepy;
		dda->side = 1;
	}
}

static void	check_doorway(t_data *data, t_dda *dda)
{
	int	value;

	if (dda->side == 1 && dda->hit == 1)
	{
		value = data->info.int_map[dda->mapy - dda->stepy][dda->mapx];
		if (value == 3 || value > DOOR_CLOSED || value < DOOR_OPENDED * -1)
			dda->hit = 3;
	}
	if (dda->side == 0 && dda->hit == 1)
	{
		value = data->info.int_map[dda->mapy][dda->mapx - dda->stepx];
		if (value == 3 || value > DOOR_CLOSED || value < DOOR_OPENDED * -1)
			dda->hit = 3;
	}
}

static void	perform_dda(t_data *data, t_dda *dda)
{
	int	value;

	dda->hit = 0;
	while (dda->hit == 0)
	{
		dda->walloffset = 0;
		get_side(dda);
		value = data->info.int_map[dda->mapy][dda->mapx];
		if (value == WALL)
			dda->hit = 1;
		else if (value == DOOR_CLOSED)
			closed_door(dda, &data->p);
		else if (value > DOOR_CLOSED)
			closing_door(dda, &data->p, value);
		else if (value < DOOR_OPENDED * -1)
			opening_door(dda, &data->p, value);
		else if (value == DOOR_OPENDED)
			opened_door(dda, &data->p);
		check_doorway(data, dda);
	}
}

static void	calc_draw_end_start(t_dda *dda, int pitch, t_point *p)
{
	if (dda->side == 0 && dda->hit != 2)
		dda->perpwalldist = (dda->mapx - p->x + dda->walloffset
				+ (1 - dda->stepx) / 2) / dda->raydirx;
	else if (dda->side == 1 && dda->hit != 2)
		dda->perpwalldist = (dda->mapy - p->y + dda->walloffset
				+ (1 - dda->stepy) / 2) / dda->raydiry;
	dda->lineheight = (int)(HEIGHT / dda->perpwalldist);
	dda->drawstart = -dda->lineheight / 2 + HEIGHT / 2 + pitch;
	if (dda->drawstart < 0)
		dda->drawstart = 0;
	dda->drawend = dda->lineheight / 2 + HEIGHT / 2 + pitch;
	if (dda->drawend >= HEIGHT)
		dda->drawend = HEIGHT - 1;
	if (dda->side == 0)
		dda->wallx = p->y + dda->perpwalldist * dda->raydiry;
	else
		dda->wallx = p->x + dda->perpwalldist * dda->raydirx;
	dda->wallx -= floor(dda->wallx);
}

static void	texture_pos(t_dda *dda, int pitch, int value)
{
	dda->texx = (int)(dda->wallx * TEX);
	if (dda->side == 0 && dda->raydirx > 0)
		dda->texx = TEX - dda->texx - 1;
	if (dda->side == 1 && dda->raydiry < 0)
		dda->texx = TEX - dda->texx - 1;
	dda->step = 1.0 * TEX / dda->lineheight;
	dda->texpos = (dda->drawstart - pitch - HEIGHT / 2 + dda->lineheight / 2)
		* dda->step;
	if (dda->hit == 2 && (value > DOOR_CLOSED || value < DOOR_OPENDED * -1))
		door_tex_correction(dda, value);
}

void	main_raycast_loop(t_dda *dda, t_data *data)
{
	int	x;
	int	value;

	x = -1;
	while (++x < WIDTH)
	{
		dda->camerax = 2 * x / (double)WIDTH - 1;
		dda->mapx = (int)data->p.x;
		dda->mapy = (int)data->p.y;
		ray_direction(data, dda);
		perform_dda(data, dda);
		calc_draw_end_start(dda, data->rays.pitch, &data->p);
		value = data->info.int_map[dda->mapy][dda->mapx];
		texture_pos(dda, data->rays.pitch, value);
		draw_loop(data, dda, x);
		data->z_buffer[x] = dda->perpwalldist;
	}
}
