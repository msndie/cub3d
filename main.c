/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/04/15 20:38:51 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	ft_close(t_data *data)
{
	// mlx_destroy_window(data->mlx.mlx, data->mlx.win);
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
		if (data->info.int_map[(int)(data->p.y + data->rays.plane_y * moveSpeed)][(int)data->p.x] != 1)
			data->p.y -= data->rays.plane_y * moveSpeed;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.plane_x * moveSpeed)] != 1)
			data->p.x -= data->rays.plane_x * moveSpeed;
		
		// data->p.x -= 0.1f;
		// render(data);
	}
	if (keycode == D)
	{
		if (data->info.int_map[(int)(data->p.y + data->rays.plane_y * moveSpeed)][(int)data->p.x] != 1)
			data->p.y += data->rays.plane_y * moveSpeed;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.plane_x * moveSpeed)] != 1)
			data->p.x += data->rays.plane_x * moveSpeed;

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
		// mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	get_tex_colour(t_img *img, int x, int y)
{
	return (*(int*)(img->addr + (4 * TEX_W * y) + (4 * x)));
}

int	loop_hook(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	// printf("dir %f %f\n", data->rays.dir_x, data->rays.dir_y);
	// printf("plane %f %f\n", data->rays.plane_x, data->rays.plane_y);


	// for(int y = HEIGHT / 2 + 1; y < HEIGHT; ++y)
	// {
	// 	float rayDirX0 = data->rays.dir_x - data->rays.plane_x;
	// 	float rayDirY0 = data->rays.dir_y - data->rays.plane_y;
	// 	float rayDirX1 = data->rays.dir_x + data->rays.plane_x;
	// 	float rayDirY1 = data->rays.dir_y + data->rays.plane_y;

	// 	// Current y position compared to the center of the screen (the horizon)
	// 	int p = y - HEIGHT / 2;

	// 	// Vertical position of the camera.
	// 	// NOTE: with 0.5, it's exactly in the center between floor and ceiling,
	// 	// matching also how the walls are being raycasted. For different values
	// 	// than 0.5, a separate loop must be done for ceiling and floor since
	// 	// they're no longer symmetrical.
	// 	float posZ = 0.5 * HEIGHT;

	// 	// Horizontal distance from the camera to the floor for the current row.
	// 	// 0.5 is the z position exactly in the middle between floor and ceiling.
	// 	// NOTE: this is affine texture mapping, which is not perspective correct
	// 	// except for perfectly horizontal and vertical surfaces like the floor.
	// 	// NOTE: this formula is explained as follows: The camera ray goes through
	// 	// the following two points: the camera itself, which is at a certain
	// 	// height (posZ), and a point in front of the camera (through an imagined
	// 	// vertical plane containing the screen pixels) with horizontal distance
	// 	// 1 from the camera, and vertical position p lower than posZ (posZ - p). When going
	// 	// through that point, the line has vertically traveled by p units and
	// 	// horizontally by 1 unit. To hit the floor, it instead needs to travel by
	// 	// posZ units. It will travel the same ratio horizontally. The ratio was
	// 	// 1 / p for going through the camera plane, so to go posZ times farther
	// 	// to reach the floor, we get that the total horizontal distance is posZ / p.
	// 	float rowDistance = posZ / p;

	// 	// calculate the real world step vector we have to add for each x (parallel to camera plane)
	// 	// adding step by step avoids multiplications with a weight in the inner loop
	// 	float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
	// 	float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

	// 	// real world coordinates of the leftmost column. This will be updated as we step to the right.
	// 	float floorX = data->p.x + rowDistance * rayDirX0;
	// 	float floorY = data->p.y + rowDistance * rayDirY0;

	// 	for(int x = 0; x < WIDTH; ++x)
	// 	{
	// 	// the cell coord is simply got from the integer parts of floorX and floorY
	// 		// int cellX = (int)(floorX);
	// 		// int cellY = (int)(floorY);

	// 		// get the texture coordinate from the fractional part
	// 		// int tx = (int)(TEX_W * (floorX - cellX)) & (TEX_W - 1);
	// 		// int ty = (int)(TEX_H * (floorY - cellY)) & (TEX_H - 1);

	// 		floorX += floorStepX;
	// 		floorY += floorStepY;

	// 		// choose texture and draw the pixel
	// 		// int checkerBoardPattern = ((int)(cellX + cellY)) & 1;
	// 		// int floorTexture;
	// 		// if(checkerBoardPattern == 0)
	// 		// 	floorTexture = 3;
	// 		// else
	// 		// 	floorTexture = 4;
	// 		// int ceilingTexture = 6;

	// 		// floor
	// 		// color = texture[floorTexture][texWidth * ty + tx];
	// 		// color = (color >> 1) & 8355711; // make a bit darker
	// 		// buffer[y][x] = color;
	// 		my_mlx_pixel_put(&data->img, x, y, data->info.f->trgb);

	// 		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
	// 		// color = texture[ceilingTexture][texWidth * ty + tx];
	// 		// color = (color >> 1) & 8355711; // make a bit darker
	// 		// buffer[screenHeight - y - 1][x] = color;
	// 		my_mlx_pixel_put(&data->img, x, HEIGHT - y - 1, data->info.c->trgb);
	// 	}
	// }


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
		int	pitch = 100;
		int drawStart = -lineHeight / 2 + HEIGHT / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2 + pitch;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		// int color = 0x00800000;
		// if (side == 1)
		// 	color = color / 2;
		// t_point	f;
		// t_point	t;
		// f.x = x;
		// f.y = drawStart;
		// t.x = x;
		// t.y = drawEnd;
		// draw_line(&data->img, color, f, t);
		
		// int	texNum = data->info.int_map[mapY][mapX] - 1;
		double wallX;
		if (side == 0)
			wallX = data->p.y + perpWallDist * rayDirY;
		else
			wallX = data->p.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)TEX_W);
		if(side == 0 && rayDirX > 0)
			texX = TEX_W - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = TEX_W - texX - 1;
		double step = 1.0 * TEX_H / lineHeight;
		double texPos = (drawStart - pitch - HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TEX_H - 1);
			texPos += step;
			// t_colour c;
			// int color = data->info.no->addr[TEX_H * texY + texX];
			// c.r = 
			// int color = data->info.no->addr[texY * TEX_W + texX * (data->info.no->bits_per_pixel / 8)];
			int color = get_tex_colour(data->info.no, texX, texY);
			// get_colour(&c, color);
			if(side == 1)
				color = (color >> 1) & 8355711;
			// my_mlx_pixel_put(&data->img, x, y, create_trgb(00, c.r, c.g, c.b));
			my_mlx_pixel_put(&data->img, x, y, color);
		}
		double floorXWall, floorYWall;
		if(side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0)
			drawEnd = HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < HEIGHT; y++)
		{
			// currentDist = HEIGHT / (2.0 * y - HEIGHT); //you could make a small lookup table for this instead

			// double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			// double currentFloorX = weight * floorXWall + (1.0 - weight) * data->p.x;
			// double currentFloorY = weight * floorYWall + (1.0 - weight) * data->p.y;

			// int floorTexX, floorTexY;
			// floorTexX = (int)(currentFloorX * TEX_W) % texWidth;
			// floorTexY = (int)(currentFloorY * TEX_H) % texHeight;

			//floor
			// buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			my_mlx_pixel_put(&data->img, x, y, data->info.f->trgb);
			//ceiling (symmetrical!)
			// buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
			my_mlx_pixel_put(&data->img, x, HEIGHT - y, data->info.c->trgb);
		}
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


	// data.mlx.mlx = mlx_init();
	// data.mlx.win = mlx_new_window(data.mlx.mlx, WIDTH, HEIGHT, "cube3d");


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