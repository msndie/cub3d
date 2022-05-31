/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:38:13 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:37:05 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

void	move_forvard(t_data *data)
{
	int	value;

	value = data->info.int_map[(int)(data->p.y + data->rays.dir_y * MV_SPEED)]
	[(int)data->p.x];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.y += data->rays.dir_y * MV_SPEED;
	value = data->info.int_map[(int)data->p.y]
	[(int)(data->p.x + data->rays.dir_x * MV_SPEED)];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.x += data->rays.dir_x * MV_SPEED;
}

void	move_back(t_data *data)
{
	int	value;

	value = data->info.int_map[(int)(data->p.y - data->rays.dir_y * MV_SPEED)]
	[(int)data->p.x];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.y -= data->rays.dir_y * MV_SPEED;
	value = data->info.int_map[(int)data->p.y]
	[(int)(data->p.x - data->rays.dir_x * MV_SPEED)];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.x -= data->rays.dir_x * MV_SPEED;
}

void	move_left(t_data *data)
{
	int	value;

	value = data->info.int_map[(int)(data->p.y - data->rays.plane_y * MV_SPEED)]
	[(int)data->p.x];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.y -= data->rays.plane_y * MV_SPEED;
	value = data->info.int_map[(int)data->p.y]
	[(int)(data->p.x - data->rays.plane_x * MV_SPEED)];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.x -= data->rays.plane_x * MV_SPEED;
}

void	move_right(t_data *data)
{
	int	value;

	value = data->info.int_map[(int)(data->p.y + data->rays.plane_y * MV_SPEED)]
	[(int)data->p.x];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.y += data->rays.plane_y * MV_SPEED;
	value = data->info.int_map[(int)data->p.y]
	[(int)(data->p.x + data->rays.plane_x * MV_SPEED)];
	if (value == EMPTY || value == DOOR_OPENDED)
		data->p.x += data->rays.plane_x * MV_SPEED;
}

void	rotate_camera(t_data *data)
{
	double	olddirx;
	double	oldplanex;
	int		min;

	oldplanex = data->rays.plane_x;
	olddirx = data->rays.dir_x;
	min = 1;
	if (data->keys.left)
		min = -1;
	data->rays.dir_x = data->rays.dir_x * cos(ROT_SPEED * min)
		- data->rays.dir_y * sin(ROT_SPEED * min);
	data->rays.dir_y = olddirx * sin(ROT_SPEED * min)
		+ data->rays.dir_y * cos(ROT_SPEED * min);
	data->rays.plane_x = data->rays.plane_x * cos(ROT_SPEED * min)
		- data->rays.plane_y * sin(ROT_SPEED * min);
	data->rays.plane_y = oldplanex * sin(ROT_SPEED * min)
		+ data->rays.plane_y * cos(ROT_SPEED * min);
}
