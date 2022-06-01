/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:40:07 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 15:17:57 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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

static void	calc_draw_end_start(t_dda *dda, t_point *p)
{
	if (dda->side == 0)
		dda->perpwalldist = dda->sidedistx - dda->deltadistx;
	else if (dda->side == 1)
		dda->perpwalldist = dda->sidedisty - dda->deltadisty;
	dda->lineheight = (int)(HEIGHT / dda->perpwalldist);
	dda->drawstart = -dda->lineheight / 2 + HEIGHT / 2 ;
	if (dda->drawstart < 0)
		dda->drawstart = 0;
	dda->drawend = dda->lineheight / 2 + HEIGHT / 2;
	if (dda->drawend >= HEIGHT)
		dda->drawend = HEIGHT - 1;
	if (dda->side == 0)
		dda->wallx = p->y + dda->perpwalldist * dda->raydiry;
	else
		dda->wallx = p->x + dda->perpwalldist * dda->raydirx;
	dda->wallx -= floor(dda->wallx);
}

static void	texture_pos(t_dda *dda)
{
	dda->texx = (int)(dda->wallx * TEX);
	if (dda->side == 0 && dda->raydirx > 0)
		dda->texx = TEX - dda->texx - 1;
	if (dda->side == 1 && dda->raydiry < 0)
		dda->texx = TEX - dda->texx - 1;
	dda->step = 1.0 * TEX / dda->lineheight;
	dda->texpos = (dda->drawstart - HEIGHT / 2 + dda->lineheight / 2)
		* dda->step;
}

void	main_raycast_loop(t_dda *dda, t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		dda->camerax = 2 * x / (double)WIDTH - 1;
		dda->mapx = (int)data->p.x;
		dda->mapy = (int)data->p.y;
		ray_direction(data, dda);
		perform_dda(data, dda);
		calc_draw_end_start(dda, &data->p);
		texture_pos(dda);
		draw_loop(data, dda, x);
	}
}
