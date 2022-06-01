/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:16 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:26:02 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

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

void	perform_dda(t_data *data, t_dda *dda)
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
