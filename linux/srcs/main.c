/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 15:08:58 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static int	ft_close(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	get_tex_colour(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (4 * TEX * y) + (4 * x)));
}

void	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
}

void	prapare_img_and_keys(t_data *data)
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
	render(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		ft_putendl_fd("Missing map", 2);
		return (1);
	}
	if (argc > 2)
		ft_putendl_fd("Only first argument will be used", 1);
	null_init(&data);
	cub_extension(argv[1]);
	data.mlx.mlx = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.mlx, WIDTH, HEIGHT, "cube3d");
	init_map(argv[1], &data);
	if (check_walls(&data))
	{
		free_all(&data);
		ft_putendl_fd("Error\nWalls problem", 2);
		exit(EXIT_FAILURE);
	}
	map_to_int(&data);
	data.dda = (t_dda *)malloc(sizeof(t_dda));
	if (!data.dda)
	{
		free_all(&data);
		exit(EXIT_FAILURE);
	}
	data.keys.a = 0;
	data.keys.s = 0;
	data.keys.w = 0;
	data.keys.d = 0;
	data.keys.left = 0;
	data.keys.right = 0;
	data.rays.pitch = 0;
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_released, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
}
