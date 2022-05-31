/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:38:58 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:37:02 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static void	horiz_mouse(t_data *data, t_mouse *current)
{
	double	olddirx;
	double	oldplanex;
	int		min;

	olddirx = data->rays.dir_x;
	oldplanex = data->rays.plane_x;
	if (data->mouse.x + 5 < current->x)
		min = 1;
	else if (data->mouse.x - 5 > current->x)
		min = -1;
	else
		return ;
	data->rays.dir_x = data->rays.dir_x * cos(ROT_SPEED * min)
		- data->rays.dir_y * sin(ROT_SPEED * min);
	data->rays.dir_y = olddirx * sin(ROT_SPEED * min)
		+ data->rays.dir_y * cos(ROT_SPEED * min);
	data->rays.plane_x = data->rays.plane_x * cos(ROT_SPEED * min)
		- data->rays.plane_y * sin(ROT_SPEED * min);
	data->rays.plane_y = oldplanex * sin(ROT_SPEED * min)
		+ data->rays.plane_y * cos(ROT_SPEED * min);
}

void	mouse_handle(t_data *data)
{
	t_mouse	current;

	mlx_mouse_get_pos(data->mlx.win, &current.x, &current.y);
	if (data->mouse.y - 5 > current.y && data->rays.pitch < 900)
		data->rays.pitch += 25;
	else if (data->mouse.y + 5 < current.y && data->rays.pitch > -900)
		data->rays.pitch -= 25;
	horiz_mouse(data, &current);
	mlx_mouse_move(data->mlx.win, WIDTH / 2, HEIGHT / 2);
}
