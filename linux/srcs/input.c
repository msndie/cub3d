/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:34:17 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 15:10:55 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.w = 1;
	else if (keycode == S)
		data->keys.s = 1;
	if (keycode == A)
		data->keys.a = 1;
	else if (keycode == D)
		data->keys.d = 1;
	if (keycode == LEFT)
		data->keys.left = 1;
	else if (keycode == RIGHT)
		data->keys.right = 1;
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.w = 0;
	else if (keycode == S)
		data->keys.s = 0;
	else if (keycode == A)
		data->keys.a = 0;
	else if (keycode == D)
		data->keys.d = 0;
	else if (keycode == LEFT)
		data->keys.left = 0;
	else if (keycode == RIGHT)
		data->keys.right = 0;
	else if (keycode == 65307)
	{
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	move_camera(t_data *data)
{
	if (data->keys.w)
		move_forvard(data);
	if (data->keys.s)
		move_back(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
}
