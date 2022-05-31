/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:38:13 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 17:49:18 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	move_forvard(t_data *data)
{
	int	x;
	int	y;

	y = data->p.y + data->rays.dir_y * MV_SPEED;
	if (y >= (int)ft_char_arr_len(data->info.map) - 1 || y <= 0)
		return ;
	x = data->p.x + data->rays.dir_x * MV_SPEED;
	if (x >= (int)ft_strlen(data->info.map[y]) - 1 || x <= 0)
		return ;
	if (data->info.map[y][x] == ' ')
		return ;
	data->p.y += data->rays.dir_y * MV_SPEED;
	data->p.x += data->rays.dir_x * MV_SPEED;
}

void	move_back(t_data *data)
{
	int	x;
	int	y;

	y = data->p.y - data->rays.dir_y * MV_SPEED;
	if (y >= (int)ft_char_arr_len(data->info.map) - 1 || y <= 0)
		return ;
	x = data->p.x - data->rays.dir_x * MV_SPEED;
	if (x >= (int)ft_strlen(data->info.map[y]) - 1 || x <= 0)
		return ;
	if (data->info.map[y][x] == ' ')
		return ;
	data->p.y -= data->rays.dir_y * MV_SPEED;
	data->p.x -= data->rays.dir_x * MV_SPEED;
}

void	move_left(t_data *data)
{
	int	x;
	int	y;

	y = data->p.y - data->rays.plane_y * MV_SPEED;
	if (y >= (int)ft_char_arr_len(data->info.map) - 1 || y <= 0)
		return ;
	x = data->p.x - data->rays.plane_x * MV_SPEED;
	if (x >= (int)ft_strlen(data->info.map[y]) - 1 || x <= 0)
		return ;
	if (data->info.map[y][x] == ' ')
		return ;
	data->p.y -= data->rays.plane_y * MV_SPEED;
	data->p.x -= data->rays.plane_x * MV_SPEED;
}

void	move_right(t_data *data)
{
	int	x;
	int	y;

	y = data->p.y + data->rays.plane_y * MV_SPEED;
	if (y >= (int)ft_char_arr_len(data->info.map) - 1 || y <= 0)
		return ;
	x = data->p.x + data->rays.plane_x * MV_SPEED;
	if (x >= (int)ft_strlen(data->info.map[y]) - 1 || x <= 0)
		return ;
	if (data->info.map[y][x] == ' ')
		return ;
	data->p.y += data->rays.plane_y * MV_SPEED;
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
