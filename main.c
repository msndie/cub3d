/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/05/27 18:56:15 by sclam            ###   ########.fr       */
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

int	get_tex_colour(t_img *img, int x, int y)
{
	return (*(int*)(img->addr + (4 * TEX * y) + (4 * x)));
}

void draw_fc(t_data *data)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		int is_floor = y > HEIGHT / 2 + data->rays.pitch;
		while (x < WIDTH)
		{
			if (is_floor)
				my_mlx_pixel_put(&data->img, x, y, data->info.f->trgb);
			else
				my_mlx_pixel_put(&data->img, x, y, data->info.c->trgb);
			x++;
		}
		y++;
	}
}

void	render(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->map.img, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->player.img, (data->p.x - 0.08) * MAP_TILE, (data->p.y - 0.08) * MAP_TILE);
}

void door_handle(t_data *data)
{
	int x;
	int y;

	if (data->info.int_map[(int)data->p.y][(int)data->p.x] == DOOR_OPENDED)
		return;
	x = data->p.x + data->rays.dir_x;
	y = data->p.y + data->rays.dir_y;
	if (data->info.int_map[y][x] == DOOR_OPENDED)
		data->info.int_map[y][x] = (data->info.int_map[y][x] * -1) - 100;
	else if (data->info.int_map[y][x] == DOOR_CLOSED)
		data->info.int_map[y][x] += 100;
}

int key_pressed(int keycode, t_data *data)
{
	if (keycode == W)
	{
		data->keys.s = 0;
		data->keys.w = 1;
	}
	else if (keycode == S)
	{
		data->keys.w = 0;
		data->keys.s = 1;
	}
	if (keycode == A)
	{
		data->keys.a = 1;
		data->keys.d = 0;
	}
	else if (keycode == D)
	{
		data->keys.d = 1;
		data->keys.a = 0;
	}
	if (keycode == LEFT)
	{
		data->keys.right = 0;
		data->keys.left = 1;
	}
	else if (keycode == RIGHT)
	{
		data->keys.left = 0;
		data->keys.right = 1;
	}
	if (keycode == TILDA)
	{
		if (data->keys.tilda)
			data->keys.tilda = 0;
		else
			data->keys.tilda = 1;
	}
	if (keycode == SPACEBAR)
		door_handle(data);
	return (0);
}

int key_released(int keycode, t_data *data)
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
	else if (keycode == 53)
	{
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void rotate_camera(t_data *data)
{
	if (data->keys.left)
	{
		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(-ROT_SPEED) - data->rays.dir_y * sin(-ROT_SPEED);
		data->rays.dir_y = oldDirX * sin(-ROT_SPEED) + data->rays.dir_y * cos(-ROT_SPEED);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(-ROT_SPEED) - data->rays.plane_y * sin(-ROT_SPEED);
		data->rays.plane_y = oldPlaneX * sin(-ROT_SPEED) + data->rays.plane_y * cos(-ROT_SPEED);
	}
	else if (data->keys.right)
	{
		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(ROT_SPEED) - data->rays.dir_y * sin(ROT_SPEED);
		data->rays.dir_y = oldDirX * sin(ROT_SPEED) + data->rays.dir_y * cos(ROT_SPEED);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(ROT_SPEED) - data->rays.plane_y * sin(ROT_SPEED);
		data->rays.plane_y = oldPlaneX * sin(ROT_SPEED) + data->rays.plane_y * cos(ROT_SPEED);
	}
}

void move_camera(t_data *data)
{
	if (data->keys.w)
	{
		if (data->info.int_map[(int)(data->p.y + data->rays.dir_y * MOVE_SPEED)][(int)data->p.x] == EMPTY
			|| data->info.int_map[(int)(data->p.y + data->rays.dir_y * MOVE_SPEED)][(int)data->p.x] == DOOR_OPENDED)
			data->p.y += data->rays.dir_y * MOVE_SPEED;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.dir_x * MOVE_SPEED)] == EMPTY
			|| data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.dir_x * MOVE_SPEED)] == DOOR_OPENDED)
			data->p.x += data->rays.dir_x * MOVE_SPEED;
	} else if (data->keys.s)
	{
		if (data->info.int_map[(int)(data->p.y - data->rays.dir_y * MOVE_SPEED)][(int)data->p.x] == EMPTY
			|| data->info.int_map[(int)(data->p.y - data->rays.dir_y * MOVE_SPEED)][(int)data->p.x] == DOOR_OPENDED)
			data->p.y -= data->rays.dir_y * MOVE_SPEED;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x - data->rays.dir_x * MOVE_SPEED)] == EMPTY
			|| data->info.int_map[(int)data->p.y][(int)(data->p.x - data->rays.dir_x * MOVE_SPEED)] == DOOR_OPENDED)
			data->p.x -= data->rays.dir_x * MOVE_SPEED;
	}
	if (data->keys.a)
	{
		if (data->info.int_map[(int)(data->p.y - data->rays.plane_y * MOVE_SPEED)][(int)data->p.x] == EMPTY
			|| data->info.int_map[(int)(data->p.y - data->rays.plane_y * MOVE_SPEED)][(int)data->p.x] == DOOR_OPENDED)
			data->p.y -= data->rays.plane_y * MOVE_SPEED;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x - data->rays.plane_x * MOVE_SPEED)] == EMPTY
			|| data->info.int_map[(int)data->p.y][(int)(data->p.x - data->rays.plane_x * MOVE_SPEED)] == DOOR_OPENDED)
			data->p.x -= data->rays.plane_x * MOVE_SPEED;
	}
	if (data->keys.d)
	{
		if (data->info.int_map[(int)(data->p.y + data->rays.plane_y * MOVE_SPEED)][(int)data->p.x] == EMPTY
			|| data->info.int_map[(int)(data->p.y + data->rays.plane_y * MOVE_SPEED)][(int)data->p.x] == DOOR_OPENDED)
			data->p.y += data->rays.plane_y * MOVE_SPEED;
		if (data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.plane_x * MOVE_SPEED)] == EMPTY
			|| data->info.int_map[(int)data->p.y][(int)(data->p.x + data->rays.plane_x * MOVE_SPEED)] == DOOR_OPENDED)
			data->p.x += data->rays.plane_x * MOVE_SPEED;
	}
}

void mouse_handle(t_data *data)
{
	t_mouse current;

	mlx_mouse_get_pos(data->mlx.win, &current.x, &current.y);
	if (data->mouse.y - 5 > current.y && data->rays.pitch < 900)
		data->rays.pitch += 25;
	else if (data->mouse.y + 5 < current.y && data->rays.pitch > -900)
		data->rays.pitch -= 25;
	if (data->mouse.x + 5 < current.x)
	{
		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(ROT_SPEED) - data->rays.dir_y * sin(ROT_SPEED);
		data->rays.dir_y = oldDirX * sin(ROT_SPEED) + data->rays.dir_y * cos(ROT_SPEED);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(ROT_SPEED) - data->rays.plane_y * sin(ROT_SPEED);
		data->rays.plane_y = oldPlaneX * sin(ROT_SPEED) + data->rays.plane_y * cos(ROT_SPEED);
	}
	else if (data->mouse.x - 5 > current.x)
	{
		double oldDirX = data->rays.dir_x;
		data->rays.dir_x = data->rays.dir_x * cos(-ROT_SPEED) - data->rays.dir_y * sin(-ROT_SPEED);
		data->rays.dir_y = oldDirX * sin(-ROT_SPEED) + data->rays.dir_y * cos(-ROT_SPEED);
		double oldPlaneX = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(-ROT_SPEED) - data->rays.plane_y * sin(-ROT_SPEED);
		data->rays.plane_y = oldPlaneX * sin(-ROT_SPEED) + data->rays.plane_y * cos(-ROT_SPEED);
	}
	mlx_mouse_move(data->mlx.win, WIDTH / 2, HEIGHT / 2);
}

void door_counter(t_data *data)
{
	for (int i = 0; i < data->info.height; i++)
	{
		for (int j = 0; j < data->info.width; j++)
		{
			if (data->info.int_map[i][j] > DOOR_CLOSED)
			{
				if (data->info.int_map[i][j] == DOOR_CLOSED + 1)
					data->info.int_map[i][j] = DOOR_OPENDED;
				else
					data->info.int_map[i][j] -= 1;
			} else if (data->info.int_map[i][j] < DOOR_OPENDED * -1)
			{
				if (data->info.int_map[i][j] == DOOR_OPENDED * -1 - 1)
					data->info.int_map[i][j] = DOOR_CLOSED;
				else
					data->info.int_map[i][j] += 1;
			}
		}
	}
}

void	calc_dist(t_data *data)
{
	t_sonic	*tmp;

	tmp = data->sonics;
	while (tmp)
	{
		tmp->dist = (data->p.x - tmp->x) * (data->p.x - tmp->x) + (data->p.y - tmp->y) * (data->p.y - tmp->y);
		tmp = tmp->next;
	}
	ft_merge_sort_list(&data->sonics);
}

int	loop_hook(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

	if (!data->keys.tilda)
		mouse_handle(data);

	draw_fc(data);

	if (data->keys.left || data->keys.right)
		rotate_camera(data);
	if (data->keys.a || data->keys.d || data->keys.s || data->keys.w)
		move_camera(data);

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
			double doorX;
			double wallyoffset;
			if (data->info.int_map[mapY][mapX] >= DOOR_CLOSED)
			{
				if (side == 1)
				{
					wallyoffset = 0.5 * stepY;
					perpWallDist = (mapY - data->p.y + wallyoffset + (1 - stepY) / 2) / rayDirY;
					doorX = data->p.x + perpWallDist * rayDirX;
					doorX -= floor(doorX);
					if (sideDistY - (deltaDistY / 2) < sideDistX)
					{
						if (data->info.int_map[mapY][mapX] == DOOR_CLOSED)
							hit = 2;
						else if (doorX <= ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100))
							hit = 2;
					}
				} else {
					wallyoffset = 0.5 * stepX;
					perpWallDist = (mapX - data->p.x + wallyoffset + (1 - stepX) / 2) / rayDirX;
					doorX = data->p.y + perpWallDist * rayDirY;
					doorX -= floor(doorX);
					if (sideDistX - (deltaDistX / 2) < sideDistY)
					{
						if (data->info.int_map[mapY][mapX] == DOOR_CLOSED)
							hit = 2;
						else if (doorX <= ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100))
							hit = 2;
					}
				}
			}
			else if (data->info.int_map[mapY][mapX] < DOOR_OPENDED * -1)
			{
				if (side == 1)
				{
					wallyoffset = 0.5 * stepY;
					perpWallDist = (mapY - data->p.y + wallyoffset + (1 - stepY) / 2) / rayDirY;
					doorX = data->p.x + perpWallDist * rayDirX;
					doorX -= floor(doorX);
					doorX = 1 - doorX;
					if (sideDistY - (deltaDistY / 2) < sideDistX)
					{
						if (doorX > ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100))
							hit = 2;
					}
				} else {
					wallyoffset = 0.5 * stepX;
					perpWallDist = (mapX - data->p.x + wallyoffset + (1 - stepX) / 2) / rayDirX;
					doorX = data->p.y + perpWallDist * rayDirY;
					doorX -= floor(doorX);
					doorX = 1 - doorX;
					if (sideDistX - (deltaDistX / 2) < sideDistY)
					{
						if (doorX > ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100))
							hit = 2;
					}
				}
			}
		}
		if(side == 0 && hit == 1)
			perpWallDist = (sideDistX - deltaDistX);
		else if (side == 1 && hit == 1)
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		double wallX;
		if (side == 0)
			wallX = data->p.y + perpWallDist * rayDirY;
		else
			wallX = data->p.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		int texX = (int)(wallX * (double)TEX);
		if(side == 0 && rayDirX > 0)
			texX = TEX - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = TEX - texX - 1;
		double step = 1.0 * TEX / lineHeight;
		double texPos = (drawStart - data->rays.pitch - HEIGHT / 2 + lineHeight / 2) * step;
		if (hit == 2 && (data->info.int_map[mapY][mapX] > DOOR_CLOSED || data->info.int_map[mapY][mapX] < DOOR_OPENDED * -1))
		{
			if (data->info.int_map[mapY][mapX] > DOOR_CLOSED)
			{
				if (side == 1 && rayDirY < 0)
					texX += ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100 * TEX);
				else if (side == 0 && rayDirX < 0)
					texX -= ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100 * TEX);
				else if (side == 1 && rayDirY >= 0)
					texX -= ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100 * TEX);
				else if (side == 0 && rayDirX >= 0)
					texX += ((double)(data->info.int_map[mapY][mapX] - DOOR_CLOSED) / 100 * TEX);
			}
			else
			{
				if (side == 1 && rayDirY < 0)
					texX -= ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (side == 0 && rayDirX < 0)
					texX += ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (side == 1 && rayDirY >= 0)
					texX += ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (side == 0 && rayDirX >= 0)
					texX -= ((double)(data->info.int_map[mapY][mapX] * -1 - DOOR_OPENDED) / 100 * TEX);
			}
			if (texX > TEX)
				texX -= (int)(texX / TEX) * TEX;
			else if (texX < 0)
				texX += (int)(abs(texX) / TEX) * TEX;
		}
		for(int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TEX - 1);
			texPos += step;
			int color = 0;
			if (side == 1 && rayDirY < 0 && hit == 1)
				color = get_tex_colour(data->info.so, texX, texY);
			else if (side == 1 && rayDirY >= 0 && hit == 1)
				color = get_tex_colour(data->info.no, texX, texY);
			else if (side == 0 && rayDirX >= 0 && hit == 1)
				color = get_tex_colour(data->info.ea, texX, texY);
			else if (side == 0 && rayDirX < 0 && hit == 1)
				color = get_tex_colour(data->info.we, texX, texY);
			else if (hit == 2)
				color = get_tex_colour(data->info.dr, texX, texY);
			if((side == 1 && rayDirY >= 0) || (side == 0 && rayDirX >= 0))
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&data->img, x, y, color);
		}

		data->z_buffer[x] = perpWallDist;

	}

	calc_dist(data);
	t_sonic	*tmp = data->sonics;
	while (tmp)
	{
		double spriteX = tmp->x - data->p.x;
		double spriteY = tmp->y - data->p.y;
		double invDet = 1.0 / (data->rays.plane_x * data->rays.dir_y - data->rays.dir_x * data->rays.plane_y);
		double transformX = invDet * (data->rays.dir_y * spriteX - data->rays.dir_x * spriteY);
		double transformY = invDet * (-data->rays.plane_y * spriteX + data->rays.plane_x * spriteY);
		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		int spriteHeight = abs((int)(HEIGHT / (transformY)));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		int spriteWidth = abs( (int) (HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < data->z_buffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEX) / spriteHeight) / 256;
					int color;
					if (tmp->stage > 40)
						color = get_tex_colour(tmp->sonic_first, texX, texY);
					else if (tmp->stage > 30)
						color = get_tex_colour(tmp->sonic_second, texX, texY);
					else if (tmp->stage > 20)
						color = get_tex_colour(tmp->sonic_third, texX, texY);
					else if (tmp->stage > 10)
						color = get_tex_colour(tmp->sonic_second, texX, texY);
					else
						color = get_tex_colour(tmp->sonic_third, texX, texY);
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&data->img, stripe, y, color);
				}
			}
		}
		--tmp->stage;
		if (tmp->stage == 0)
			tmp->stage = 50;
		tmp = tmp->next;
	}

	door_counter(data);
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
	draw_player(&data);
	draw_map(&data);
	mlx_mouse_hide();
	mlx_mouse_move(data.mlx.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_get_pos(data.mlx.win, &data.mouse.x, &data.mouse.y);
	data.keys.a = 0;
	data.keys.s = 0;
	data.keys.w = 0;
	data.keys.d = 0;
	data.keys.left = 0;
	data.keys.right = 0;
	data.keys.tilda = 1;
	data.rays.pitch = 0;
	data.z_buffer = (double*)malloc(sizeof(double) * WIDTH);
	if (!data.z_buffer)
	{
		free_all(&data);
		exit(EXIT_FAILURE);
	}
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	// mlx_hook(data.mlx.win, 2, 1L << 0, ft_key_hook, &data);
	// mlx_hook(data.mlx.win, 6, 1L << 0, mouse_handle, &data);
	mlx_hook(data.mlx.win, 2, 0, key_pressed, &data);
	mlx_hook(data.mlx.win, 3, 0, key_released, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
}