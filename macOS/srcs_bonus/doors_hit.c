/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:17:33 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:18:03 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

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
