/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:43:39 by sclam             #+#    #+#             */
/*   Updated: 2022/05/28 20:41:48 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	draw_fc(t_data *data)
{
	int	y;
	int	x;
	int	is_floor;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		if (y > HEIGHT / 2 + data->rays.pitch)
			is_floor = 1;
		else
			is_floor = 0;
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
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->player.img,
		(data->p.x - 0.08) * MAP_TILE, (data->p.y - 0.08) * MAP_TILE);
}

void	door_handle(t_data *data)
{
	int	x;
	int	y;

	if (data->info.int_map[(int)data->p.y][(int)data->p.x] == DOOR_OPENDED)
		return ;
	x = data->p.x + data->rays.dir_x;
	y = data->p.y + data->rays.dir_y;
	if (data->info.int_map[y][x] == DOOR_OPENDED)
		data->info.int_map[y][x] = (data->info.int_map[y][x] * -1) - 100;
	else if (data->info.int_map[y][x] == DOOR_CLOSED)
		data->info.int_map[y][x] += 100;
}

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
	else if (keycode == 53)
	{
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
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

void	mouse_handle(t_data *data)
{
	t_mouse	current;
	double	olddirx;
	double	oldplanex;
	int		min;

	mlx_mouse_get_pos(data->mlx.win, &current.x, &current.y);
	if (data->mouse.y - 5 > current.y && data->rays.pitch < 900)
		data->rays.pitch += 25;
	else if (data->mouse.y + 5 < current.y && data->rays.pitch > -900)
		data->rays.pitch -= 25;
	olddirx = data->rays.dir_x;
	oldplanex = data->rays.plane_x;
	if (data->mouse.x + 5 < current.x)
		min = 1;
	else if (data->mouse.x - 5 > current.x)
		min = -1;
	else
	{
		mlx_mouse_move(data->mlx.win, WIDTH / 2, HEIGHT / 2);
		return ;
	}
	data->rays.dir_x = data->rays.dir_x * cos(ROT_SPEED * min)
		- data->rays.dir_y * sin(ROT_SPEED * min);
	data->rays.dir_y = olddirx * sin(ROT_SPEED * min)
		+ data->rays.dir_y * cos(ROT_SPEED * min);
	data->rays.plane_x = data->rays.plane_x * cos(ROT_SPEED * min)
		- data->rays.plane_y * sin(ROT_SPEED * min);
	data->rays.plane_y = oldplanex * sin(ROT_SPEED * min)
		+ data->rays.plane_y * cos(ROT_SPEED * min);
	mlx_mouse_move(data->mlx.win, WIDTH / 2, HEIGHT / 2);
}

void	door_counter(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->info.height)
	{
		j = -1;
		while (++j < data->info.width)
		{
			if (data->info.int_map[i][j] > DOOR_CLOSED)
			{
				if (data->info.int_map[i][j] == DOOR_CLOSED + 2)
					data->info.int_map[i][j] = DOOR_OPENDED;
				else
					data->info.int_map[i][j] -= 2;
			}
			else if (data->info.int_map[i][j] < DOOR_OPENDED * -1)
			{
				if (data->info.int_map[i][j] == DOOR_OPENDED * -1 - 2)
					data->info.int_map[i][j] = DOOR_CLOSED;
				else
					data->info.int_map[i][j] += 2;
			}
		}
	}
}

void	calc_dist(t_data *data)
{
	t_anim	*tmp;

	tmp = data->anims;
	while (tmp)
	{
		tmp->dist = pow(data->p.x - tmp->x, 2) + pow(data->p.y - tmp->y, 2);
		tmp = tmp->next;
	}
	ft_merge_sort_list(&data->anims);
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
	if (!data->keys.tilda)
		mouse_handle(data);
	if (data->keys.left || data->keys.right)
		rotate_camera(data);
	move_camera(data);
	draw_fc(data);
}

void	ray_direction(t_data *data, t_dda *dda)
{
	dda->raydirx = data->rays.dir_x + data->rays.plane_x * dda->camerax;
	dda->raydiry = data->rays.dir_y + data->rays.plane_y * dda->camerax;
	// dda->deltadistx = (dda->raydirx == 0) ? 1e30 : fabs(1 / dda->raydirx);
	// dda->deltadisty = (dda->raydiry == 0) ? 1e30 : fabs(1 / dda->raydiry);
	dda->deltadistx = fabs(1 / dda->raydirx);
	dda->deltadisty = fabs(1 / dda->raydiry);
	if (dda->raydirx < 0)
	{
		dda->stepx = -1;
		dda->sidedistx = (data->p.x - dda->mapx) * dda->deltadistx;
	}
	else
	{
		dda->stepx = 1;
		dda->sidedistx = (dda->mapx + 1.0 - data->p.x) * dda->deltadistx;
	}
	if(dda->raydiry < 0)
	{
		dda->stepy = -1;
		dda->sidedisty = (data->p.y - dda->mapy) * dda->deltadisty;
	}
	else
	{
		dda->stepy = 1;
		dda->sidedisty = (dda->mapy + 1.0 - data->p.y) * dda->deltadisty;
	}
}

void	perform_dda(t_data *data, t_dda *dda)
{
	while(dda->hit == 0)
	{
		if(dda->sidedistx < dda->sidedisty)
		{
			dda->sidedistx += dda->deltadistx;
			dda->mapx += dda->stepx;
			dda->side = 0;
		}
		else
		{
			dda->sidedisty += dda->deltadisty;
			dda->mapy += dda->stepy;
			dda->side = 1;
		}
		if(data->info.int_map[dda->mapy][dda->mapx] == WALL)
			dda->hit = 1;
		
		if (data->info.int_map[dda->mapy][dda->mapx] >= DOOR_CLOSED)
		{
			if (dda->side == 1)
			{
				dda->wallyoffset = 0.5 * dda->stepy;
				dda->perpwalldist = (dda->mapy - data->p.y + dda->wallyoffset + (1 - dda->stepy) / 2) / dda->raydiry;
				dda->doorx = data->p.x + dda->perpwalldist * dda->raydirx;
				dda->doorx -= floor(dda->doorx);
				if (dda->sidedisty - (dda->deltadisty / 2) < dda->sidedistx)
				{
					if (data->info.int_map[dda->mapy][dda->mapx] == DOOR_CLOSED)
						dda->hit = 2;
					else if (dda->doorx <= ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100))
						dda->hit = 2;
				}
			} else {
				dda->wallyoffset = 0.5 * dda->stepx;
				dda->perpwalldist = (dda->mapx - data->p.x + dda->wallyoffset + (1 - dda->stepx) / 2) / dda->raydirx;
				dda->doorx = data->p.y + dda->perpwalldist * dda->raydiry;
				dda->doorx -= floor(dda->doorx);
				if (dda->sidedistx - (dda->deltadistx / 2) < dda->sidedisty)
				{
					if (data->info.int_map[dda->mapy][dda->mapx] == DOOR_CLOSED)
						dda->hit = 2;
					else if (dda->doorx <= ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100))
						dda->hit = 2;
				}
			}
		}
		else if (data->info.int_map[dda->mapy][dda->mapx] < DOOR_OPENDED * -1)
		{
			if (dda->side == 1)
			{
				dda->wallyoffset = 0.5 * dda->stepy;
				dda->perpwalldist = (dda->mapy - data->p.y + dda->wallyoffset + (1 - dda->stepy) / 2) / dda->raydiry;
				dda->doorx = data->p.x + dda->perpwalldist * dda->raydirx;
				dda->doorx -= floor(dda->doorx);
				dda->doorx = 1 - dda->doorx;
				if (dda->sidedisty - (dda->deltadisty / 2) < dda->sidedistx)
				{
					if (dda->doorx > ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100))
						dda->hit = 2;
				}
			} else {
				dda->wallyoffset = 0.5 * dda->stepx;
				dda->perpwalldist = (dda->mapx - data->p.x + dda->wallyoffset + (1 - dda->stepx) / 2) / dda->raydirx;
				dda->doorx = data->p.y + dda->perpwalldist * dda->raydiry;
				dda->doorx -= floor(dda->doorx);
				dda->doorx = 1 - dda->doorx;
				if (dda->sidedistx - (dda->deltadistx / 2) < dda->sidedisty)
				{
					if (dda->doorx > ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100))
						dda->hit = 2;
				}
			}
		}
	}
}

int	loop_hook(t_data *data)
{
	t_dda	*dda;
	int		x;

	dda = data->dda;
	prapare_img_and_keys(data);
	x = -1;
	while (++x < WIDTH)
	{
		dda->camerax = 2 * x / (double)WIDTH - 1;
		dda->mapx = (int)data->p.x;
		dda->mapy = (int)data->p.y;
		dda->hit = 0;
		ray_direction(data, dda);
		perform_dda(data, dda);
		if(dda->side == 0 && dda->hit == 1)
			dda->perpwalldist = (dda->sidedistx - dda->deltadistx);
		else if (dda->side == 1 && dda->hit == 1)
			dda->perpwalldist = (dda->sidedisty - dda->deltadisty);
		dda->lineheight = (int)(HEIGHT / dda->perpwalldist);
		dda->drawstart = -dda->lineheight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (dda->drawstart < 0)
			dda->drawstart = 0;
		dda->drawend = dda->lineheight / 2 + HEIGHT / 2 + data->rays.pitch;
		if (dda->drawend >= HEIGHT)
			dda->drawend = HEIGHT - 1;
		if (dda->side == 0)
			dda->wallx = data->p.y + dda->perpwalldist * dda->raydiry;
		else
			dda->wallx = data->p.x + dda->perpwalldist * dda->raydirx;
		dda->wallx -= floor((dda->wallx));
		dda->texx = (int)(dda->wallx * (double)TEX);
		if(dda->side == 0 && dda->raydirx > 0)
			dda->texx = TEX - dda->texx - 1;
		if(dda->side == 1 && dda->raydiry < 0)
			dda->texx = TEX - dda->texx - 1;
		dda->step = 1.0 * TEX / dda->lineheight;
		dda->texpos = (dda->drawstart - data->rays.pitch - HEIGHT / 2 + dda->lineheight / 2) * dda->step;
		if (dda->hit == 2 && (data->info.int_map[dda->mapy][dda->mapx] > DOOR_CLOSED || data->info.int_map[dda->mapy][dda->mapx] < DOOR_OPENDED * -1))
		{
			if (data->info.int_map[dda->mapy][dda->mapx] > DOOR_CLOSED)
			{
				if (dda->side == 1 && dda->raydiry < 0)
					dda->texx += ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100 * TEX);
				else if (dda->side == 0 && dda->raydirx < 0)
					dda->texx -= ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100 * TEX);
				else if (dda->side == 1 && dda->raydiry >= 0)
					dda->texx -= ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100 * TEX);
				else if (dda->side == 0 && dda->raydirx >= 0)
					dda->texx += ((double)(data->info.int_map[dda->mapy][dda->mapx] - DOOR_CLOSED) / 100 * TEX);
			}
			else
			{
				if (dda->side == 1 && dda->raydiry < 0)
					dda->texx -= ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (dda->side == 0 && dda->raydirx < 0)
					dda->texx += ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (dda->side == 1 && dda->raydiry >= 0)
					dda->texx += ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100 * TEX);
				else if (dda->side == 0 && dda->raydirx >= 0)
					dda->texx -= ((double)(data->info.int_map[dda->mapy][dda->mapx] * -1 - DOOR_OPENDED) / 100 * TEX);
			}
			if (dda->texx > TEX)
				dda->texx -= (int)(dda->texx / TEX) * TEX;
			else if (dda->texx < 0)
				dda->texx += (int)(abs(dda->texx) / TEX) * TEX;
		}
		for(int y = dda->drawstart; y < dda->drawend; y++)
		{
			int texY = (int)dda->texpos & (TEX - 1);
			dda->texpos += dda->step;
			int color = 0;
			if (dda->side == 1 && dda->raydiry < 0 && dda->hit == 1)
				color = get_tex_colour(data->info.so, dda->texx, texY);
			else if (dda->side == 1 && dda->raydiry >= 0 && dda->hit == 1)
				color = get_tex_colour(data->info.no, dda->texx, texY);
			else if (dda->side == 0 && dda->raydirx >= 0 && dda->hit == 1)
				color = get_tex_colour(data->info.ea, dda->texx, texY);
			else if (dda->side == 0 && dda->raydirx < 0 && dda->hit == 1)
				color = get_tex_colour(data->info.we, dda->texx, texY);
			else if (dda->hit == 2)
				color = get_tex_colour(data->info.dr, dda->texx, texY);
			if((dda->side == 1 && dda->raydiry >= 0) || (dda->side == 0 && dda->raydirx >= 0))
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&data->img, x, y, color);
		}

		data->z_buffer[x] = dda->perpwalldist;

	}

	calc_dist(data);
	t_anim	*tmp = data->anims;
	while (tmp)
	{
		double spriteX = tmp->x - data->p.x;
		double spriteY = tmp->y - data->p.y;
		double invDet = 1.0 / (data->rays.plane_x * data->rays.dir_y - data->rays.dir_x * data->rays.plane_y);
		double transformX = invDet * (data->rays.dir_y * spriteX - data->rays.dir_x * spriteY);
		double transformY = invDet * (-data->rays.plane_y * spriteX + data->rays.plane_x * spriteY);
		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		int	vMoveScreen = (int)(0.0 / transformY) + data->rays.pitch;
		int spriteHeight = abs((int)(HEIGHT / (transformY)));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2 + vMoveScreen;
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
			dda->texx = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < data->z_buffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y - vMoveScreen) * 256 - HEIGHT * 128 + spriteHeight * 128;
					int texY = ((d * TEX) / spriteHeight) / 256;
					int color;
					if (tmp->stage > 70)
						color = get_tex_colour(tmp->anim_first, dda->texx, texY);
					else if (tmp->stage > 60)
						color = get_tex_colour(tmp->anim_second, dda->texx, texY);
					else if (tmp->stage > 50)
						color = get_tex_colour(tmp->anim_third, dda->texx, texY);
					else if (tmp->stage > 40)
						color = get_tex_colour(tmp->anim_second, dda->texx, texY);
					else if (tmp->stage > 30)
						color = get_tex_colour(tmp->anim_third, dda->texx, texY);
					else if (tmp->stage > 20)
						color = get_tex_colour(tmp->anim_second, dda->texx, texY);
					else
						color = get_tex_colour(tmp->anim_first, dda->texx, texY);
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&data->img, stripe, y, color);
				}
			}
		}
		--tmp->stage;
		if (tmp->stage == 0)
			tmp->stage = 150;
		tmp = tmp->next;
	}

	door_counter(data);
	render(data);
	return (0);
}

int	sprites_create(t_data *data)
{
	size_t	i;
	size_t	j;
	t_anim	*tmp;

	i = -1;
	while (++i < ft_char_arr_len(data->info.map))
	{
		j = -1;
		while (++j < ft_strlen(data->info.map[i]))
		{
			if (data->info.map[i][j] == 'H')
			{
				if (ft_lst_add_back(&data->anims, ft_lst_new(j, i)))
					return (1);
				tmp = ft_lst_last(data->anims);
				tmp->anim_first = data->info.anim_first;
				tmp->anim_second = data->info.anim_second;
				tmp->anim_third = data->info.anim_third;
				ft_lst_last(data->anims)->stage = 150;
			}	
		}
	}
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
	if (sprites_create(&data))
	{
		free_all(&data);
		ft_putendl_fd("Error\nMalloc", 2);
		exit(EXIT_FAILURE);
	}
	map_to_int(&data);
	draw_player(&data);
	draw_map(&data);
	data.z_buffer = (double*)malloc(sizeof(double) * WIDTH);
	if (!data.z_buffer)
	{
		free_all(&data);
		exit(EXIT_FAILURE);
	}
	data.dda = (t_dda*)malloc(sizeof(t_dda));
	if (!data.dda)
	{
		free_all(&data);
		exit(EXIT_FAILURE);
	}
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
	mlx_hook(data.mlx.win, 17, 0, ft_close, &data);
	mlx_hook(data.mlx.win, 2, 0, key_pressed, &data);
	mlx_hook(data.mlx.win, 3, 0, key_released, &data);
	mlx_loop_hook(data.mlx.mlx, loop_hook, &data);
	mlx_loop(data.mlx.mlx);
}
