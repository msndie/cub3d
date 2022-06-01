/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 15:23:10 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static int	ft_close(t_data *data)
{
	free_all(data);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	bad_exit(t_data *data, char *str)
{
	free_all(data);
	if (str)
		ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

static int	check(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl_fd("Missing map", 2);
		return (1);
	}
	if (argc > 2)
		ft_putendl_fd("Only first argument will be used", 1);
	cub_extension(argv[1]);
	return (0);
}

static void	prepare(t_data *data, char **argv)
{
	init_map(argv[1], data);
	if (check_walls(data))
		bad_exit(data, "Error\nWalls problem");
	if (sprites_create(data))
		bad_exit(data, "Error\nMalloc");
	map_to_int(data);
	draw_player(data);
	draw_map(data, -1, -1);
	data->z_buffer = (double *)malloc(sizeof(double) * WIDTH);
	if (!data->z_buffer)
		bad_exit(data, "Error\nMalloc");
	data->dda = (t_dda *)malloc(sizeof(t_dda));
	if (!data->dda)
		bad_exit(data, "Error\nMalloc");
}

int	main(int argc, char **argv)
{
	t_data	data;

	null_init(&data);
	if (check(argc, argv))
		return (1);
	data.mlx.mlx = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.mlx, WIDTH, HEIGHT, "cub3d");
	prepare(&data, argv);
	mlx_mouse_hide(data.mlx.mlx, data.mlx.win);
	mlx_mouse_move(data.mlx.mlx, data.mlx.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_get_pos(data.mlx.mlx, data.mlx.win, &data.mouse.x, &data.mouse.y);
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_released, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
}
