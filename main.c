/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/04/14 20:12:57 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free_all(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->map.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->player.img, (data->p.x - 0.08) * MAP_TILE, (data->p.y - 0.08) * MAP_TILE);
}

static int	ft_key_hook(int keycode, t_data *data)
{
	double	moveSpeed;
	double	rotSpeed;

	moveSpeed = 0.15;
	rotSpeed = 0.1;
	if (keycode == W)
	{
		// if ((int)(data->p.y + data->rays.dir_y * moveSpeed) >= 0 && (int)(data->p.y + data->rays.dir_y * moveSpeed) < data->info.height)
		// {
		// 	printf("%d - y", (int)(data->p.y + data->rays.dir_y * moveSpeed));
		// 	// if (data->info.int_map[(int)(data->p.y + data->rays.dir_y * moveSpeed)][(int)data->p.x] != 1)
		// 		data->p.y += data->rays.dir_y * moveSpeed;
		// }
		// if ((int)(data->p.x + data->rays.dir_x * moveSpeed) >= 0 && (int)(data->p.x + data->rays.dir_x * moveSpeed) < data->info.width)
		// {
		// 	printf("    %d - x\n", (int)(data->p.x + data->rays.dir_x * moveSpeed));
		// 	// if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.dir_x * moveSpeed)] != 1)
		// 		data->p.x += data->rays.dir_x * moveSpeed;
		// }

		if (data->info.int_map[(int)(data->p.y + data->rays.dir_y * moveSpeed)][(int)data->p.x] != 1)
			data->p.y += data->rays.dir_y * moveSpeed;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.dir_x * moveSpeed)] != 1)
			data->p.x += data->rays.dir_x * moveSpeed;

	}
	if (keycode == S)
	{


		// if (data->info.int_map[(int)(data->p.x - data->dir_x * moveSpeed)][(int)data->p.y] != 1)
		// 	data->p.x -= data->dir_x * moveSpeed;
		// if (data->info.int_map[(int)data->p.x][(int)(data->p.y - data->dir_y * moveSpeed)] != 1)
		// 	data->p.y -= data->dir_y * moveSpeed;

		if (data->info.int_map[(int)(data->p.y - data->rays.dir_y * moveSpeed)][(int)data->p.x] != 1)
			data->p.y -= data->rays.dir_y * moveSpeed;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x - data->rays.dir_x * moveSpeed)] != 1)
			data->p.x -= data->rays.dir_x * moveSpeed;

	}
	if (keycode == A)
	{
		// data->p.x -= 0.1f;
		// render(data);
	}
	if (keycode == D)
	{
		// data->p.x += 0.1f;
		// render(data);
	}
	if (keycode == LEFT)
	{


		// double oldDirX = data->dir_x;
		// data->dir_x = data->dir_x * cos(rotSpeed) - data->dir_y * sin(rotSpeed);
		// data->dir_y = oldDirX * sin(rotSpeed) + data->dir_y * cos(rotSpeed);
		// double oldPlaneX = data->plane_x;
		// data->plane_x = data->plane_x * cos(rotSpeed) - data->plane_y * sin(rotSpeed);
		// data->plane_y = oldPlaneX * sin(rotSpeed) + data->plane_y * cos(rotSpeed);

		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(-rotSpeed) - data->rays.dir_y * sin(-rotSpeed);
		data->rays.dir_y = oldDirX * sin(-rotSpeed) + data->rays.dir_y * cos(-rotSpeed);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(-rotSpeed) - data->rays.plane_y * sin(-rotSpeed);
		data->rays.plane_y = oldPlaneX * sin(-rotSpeed) + data->rays.plane_y * cos(-rotSpeed);
	}
	if (keycode == RIGHT)
	{

		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(rotSpeed) - data->rays.dir_y * sin(rotSpeed);
		data->rays.dir_y = oldDirX * sin(rotSpeed) + data->rays.dir_y * cos(rotSpeed);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(rotSpeed) - data->rays.plane_y * sin(rotSpeed);
		data->rays.plane_y = oldPlaneX * sin(rotSpeed) + data->rays.plane_y * cos(rotSpeed);

		// double oldDirX = data->dir_x;
		// data->dir_x = data->dir_x * cos(-rotSpeed) - data->dir_y * sin(-rotSpeed);
		// data->dir_y = oldDirX * sin(-rotSpeed) + data->dir_y * cos(-rotSpeed);
		// double oldPlaneX = data->plane_x;
		// data->plane_x = data->plane_x * cos(-rotSpeed) - data->plane_y * sin(-rotSpeed);
		// data->plane_y = oldPlaneX * sin(-rotSpeed) + data->plane_y * cos(-rotSpeed);
	}
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	loop_hook(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	printf("dir %f %f\n", data->rays.dir_x, data->rays.dir_y);
	printf("plane %f %f\n", data->rays.plane_x, data->rays.plane_y);
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = data->rays.dir_x + data->rays.plane_x * cameraX;
		double rayDirY = data->rays.dir_y + data->rays.plane_y * cameraX;
		int mapX = (int)data->p.x;
		int mapY = (int)data->p.y;
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0;
		int side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->p.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->p.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->p.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->p.y) * deltaDistY;
		}
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(data->info.int_map[mapY][mapX] == WALL)
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		int color = 0x00800000;
		if (side == 1)
			color = color / 2;
		t_point	f;
		t_point	t;
		f.x = x;
		f.y = drawStart;
		t.x = x;
		t.y = drawEnd;
		draw_line(&data->img, color, f, t);
	}
	render(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		ft_putendl_fd("Missing map", 2);
		return (1);
	}
	if (argc > 2)
		ft_putendl_fd("Only first argument will be used", 1);
	cub_extension(argv[1]);
	null_init(&data);
	init_map(argv[1], &data);
	if (check_walls(&data))
	{
		free_all(&data);
		ft_putendl_fd("Error\nWalls problem", 2);
		exit(EXIT_FAILURE);
	}
	map_to_int(&data);
	// for (int i = 0; i < data.info.height; i++)
	// {
	// 	for (int j = 0; j < data.info.width; j++)
	// 	{
	// 		printf("%d", data.info.int_map[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// for (int i = 0; data.info.map[i]; i++)
	// {
	// 	printf("%s\n", data.info.map[i]);
	// }
	// printf("%zu\n", ft_char_arr_len(data.info.map));
	// printf("%d - c\n", data.info.c->trgb);
	// printf("%d - f\n", data.info.f->trgb);
	// printf("%s\n", data.info.ea);
	// printf("%s\n", data.info.no);
	// printf("%s\n", data.info.we);
	// printf("%s\n", data.info.so);
	// data.pdx = cos(data.pa) * 5;
	// data.pdy = sin(data.pa) * 5;

	data.mlx.mlx = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.mlx, WIDTH, HEIGHT, "cube3d");
	// data.img.img = mlx_new_image(data.mlx.mlx, 1024, 768);
	// data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	// t_point f;
	// t_point	t;
	// f.x = 5;
	// t.x = 5;
	// f.y = 203;
	// t.y = 565;
	// draw_line(&data.img, 0x00000000, f, t);
	// mlx_put_image_to_window()
	draw_player(&data);
	draw_map(&data);
	// render(&data);
	// loop_hook(&data);
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, ft_key_hook, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
}