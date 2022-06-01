/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:36:51 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:37:32 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static void	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
	if (data->keys.m)
	{
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
			data->map.img, 0, 0);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->player.img,
			(data->p.x - 0.08) * MAP_TILE, (data->p.y - 0.08) * MAP_TILE);
	}
}

static void	prapare_img_and_keys(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->img.img)
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits,
			&data->img.line_length, &data->img.endian);
	if (!data->keys.tilda)
		mouse_handle(data);
	if (data->keys.left || data->keys.right)
		rotate_camera(data);
	move_camera(data);
}

int	loop_hook(t_data *data)
{
	t_dda	*dda;

	dda = data->dda;
	prapare_img_and_keys(data);
	draw_fc(data);
	main_raycast_loop(dda, data);
	sprites_handle(data);
	door_counter(data);
	render(data);
	return (0);
}
