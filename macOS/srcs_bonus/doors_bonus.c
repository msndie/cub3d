/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:36:04 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:36:36 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

void	door_handle(t_data *data)
{
	int	x;
	int	y;

	if (data->info.int_map[(int)data->p.y][(int)data->p.x] == DOOR_OPENDED)
		return ;
	x = data->p.x + data->rays.dir_x;
	y = data->p.y + data->rays.dir_y;
	if (data->info.int_map[y][x] == DOOR_OPENDED)
		data->info.int_map[y][x] = (data->info.int_map[y][x] * -1) - 100;
	else if (data->info.int_map[y][x] == DOOR_CLOSED)
		data->info.int_map[y][x] += 100;
}

void	door_counter(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->info.height)
	{
		j = -1;
		while (++j < data->info.width)
		{
			if (data->info.int_map[i][j] > DOOR_CLOSED)
			{
				if (data->info.int_map[i][j] == DOOR_CLOSED + DOOR_SPEED)
					data->info.int_map[i][j] = DOOR_OPENDED;
				else
					data->info.int_map[i][j] -= DOOR_SPEED;
			}
			else if (data->info.int_map[i][j] < DOOR_OPENDED * -1)
			{
				if (data->info.int_map[i][j] == DOOR_OPENDED * -1 - DOOR_SPEED)
					data->info.int_map[i][j] = DOOR_CLOSED;
				else
					data->info.int_map[i][j] += DOOR_SPEED;
			}
		}
	}
}

int	calc_offset(t_dda *dda, t_point *p)
{
	if (dda->side == 1)
	{
		dda->walloffset = 0.5 * dda->stepy;
		dda->perpwalldist = (dda->mapy - p->y + dda->walloffset
				+ (1 - dda->stepy) / 2) / dda->raydiry;
		dda->wallx = p->x + dda->perpwalldist * dda->raydirx;
		if (dda->sidedisty - (dda->deltadisty / 2) < dda->sidedistx)
			return (0);
		dda->mapx += dda->stepx;
	}
	else
	{
		dda->walloffset = 0.5 * dda->stepx;
		dda->perpwalldist = (dda->mapx - p->x + dda->walloffset
				+ (1 - dda->stepx) / 2) / dda->raydirx;
		dda->wallx = p->y + dda->perpwalldist * dda->raydiry;
		if (dda->sidedistx - (dda->deltadistx / 2) < dda->sidedisty)
			return (0);
		dda->mapy += dda->stepy;
	}
	dda->side = dda->side ^ 1;
	dda->walloffset = 0;
	dda->hit = 3;
	return (1);
}

void	opening_door(t_dda *dda, t_point *p, int value)
{
	if (calc_offset(dda, p))
		return ;
	dda->wallx -= floor(dda->wallx);
	dda->wallx = 1 - dda->wallx;
	if (dda->wallx > ((double)(value * -1 - DOOR_OPENDED) / 100))
		dda->hit = 2;
}

void	closing_door(t_dda *dda, t_point *p, int value)
{
	if (calc_offset(dda, p))
		return ;
	dda->wallx -= floor(dda->wallx);
	if (dda->wallx <= ((double)(value - DOOR_CLOSED) / 100))
		dda->hit = 2;
}

void	closed_door(t_dda *dda, t_point *p)
{
	if (calc_offset(dda, p))
		return ;
	dda->hit = 2;
}

void	opened_door(t_dda *dda, t_point *p)
{
	calc_offset(dda, p);
}

void	door_tex_correction(t_dda *dda, int value)
{
	if (value > DOOR_CLOSED)
	{
		if ((dda->side == 1 && dda->raydiry < 0)
			|| (dda->side == 0 && dda->raydirx >= 0))
			dda->texx += ((double)(value - DOOR_CLOSED) / 100 * TEX);
		else if ((dda->side == 1 && dda->raydiry >= 0)
			|| (dda->side == 0 && dda->raydirx < 0))
			dda->texx -= ((double)(value - DOOR_CLOSED) / 100 * TEX);
	}
	else
	{
		if ((dda->side == 1 && dda->raydiry < 0)
			|| (dda->side == 0 && dda->raydirx >= 0))
			dda->texx -= ((double)(value * -1 - DOOR_OPENDED) / 100 * TEX);
		else if ((dda->side == 0 && dda->raydirx < 0)
			|| (dda->side == 1 && dda->raydiry >= 0))
			dda->texx += ((double)(value * -1 - DOOR_OPENDED) / 100 * TEX);
	}
	if (dda->texx > TEX)
		dda->texx -= (int)(dda->texx / TEX) * TEX;
	else if (dda->texx < 0)
		dda->texx += TEX * (int)(abs(dda->texx) / TEX);
}