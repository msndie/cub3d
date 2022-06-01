/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:40:43 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:41:27 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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

void	perform_dda(t_data *data, t_dda *dda)
{
	int	value;

	dda->hit = 0;
	while (dda->hit == 0)
	{
		get_side(dda);
		if (dda->mapy >= (int)ft_char_arr_len(data->info.map) - 1
			|| dda->mapy < 0)
			dda->hit = 2;
		else if (dda->mapx >= (int)ft_strlen(data->info.map[dda->mapy]) - 1
			|| dda->mapx < 0)
			dda->hit = 2;
		else if (data->info.map[dda->mapy][dda->mapx] == ' ')
			dda->hit = 2;
		else
		{
			value = data->info.int_map[dda->mapy][dda->mapx];
			if (value == WALL)
				dda->hit = 1;
		}
	}
}
