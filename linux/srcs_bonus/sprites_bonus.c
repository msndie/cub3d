/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:28:12 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:37:22 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static void	sprites_calc_dist(t_data *data)
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

static void	sprites_start_end(t_data *data, t_sprites *spr)
{
	spr->inv_det = 1.0 / (data->rays.plane_x * data->rays.dir_y
			- data->rays.dir_x * data->rays.plane_y);
	spr->transform_x = spr->inv_det * (data->rays.dir_y * spr->sprite_x
			- data->rays.dir_x * spr->sprite_y);
	spr->transform_y = spr->inv_det * (-data->rays.plane_y * spr->sprite_x
			+ data->rays.plane_x * spr->sprite_y);
	spr->sprite_screen_x = (int)((WIDTH / 2)
			* (1 + spr->transform_x / spr->transform_y));
	spr->sprite_height = abs((int)(HEIGHT / (spr->transform_y)));
	spr->draw_start_y = -spr->sprite_height / 2
		+ HEIGHT / 2 + data->rays.pitch;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	spr->draw_end_y = spr->sprite_height / 2 + HEIGHT / 2 + data->rays.pitch;
	if (spr->draw_end_y >= HEIGHT)
		spr->draw_end_y = HEIGHT - 1;
	spr->sprite_width = abs((int)(HEIGHT / spr->transform_y));
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_end_x >= WIDTH)
		spr->draw_end_x = WIDTH - 1;
}

static void	sprites_y_loop(t_data *data, t_sprites *spr, t_anim *tmp, int x)
{
	int	y;
	int	color;

	y = spr->draw_start_y - 1;
	while (++y < spr->draw_end_y)
	{
		spr->d = (y - data->rays.pitch) * 256 - HEIGHT
			* 128 + spr->sprite_height * 128;
		spr->texy = ((spr->d * TEX) / spr->sprite_height) / 256;
		if (tmp->stage > 60 && tmp->stage <= 70)
			color = get_tex_colour(tmp->anim_second, spr->texx, spr->texy);
		else if (tmp->stage > 50 && tmp->stage <= 60)
			color = get_tex_colour(tmp->anim_third, spr->texx, spr->texy);
		else if (tmp->stage > 40 && tmp->stage <= 50)
			color = get_tex_colour(tmp->anim_second, spr->texx, spr->texy);
		else if (tmp->stage > 30 && tmp->stage <= 40)
			color = get_tex_colour(tmp->anim_third, spr->texx, spr->texy);
		else if (tmp->stage > 20 && tmp->stage <= 30)
			color = get_tex_colour(tmp->anim_second, spr->texx, spr->texy);
		else
			color = get_tex_colour(tmp->anim_first, spr->texx, spr->texy);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&data->img, x, y, color);
	}
}

static void	sprites_x_loop(t_data *data, t_sprites *spr, t_anim *tmp)
{
	int	x;

	x = spr->draw_start_x - 1;
	while (++x < spr->draw_end_x)
	{
		spr->texx = (int)(256 * (x - (-spr->sprite_width / 2
						+ spr->sprite_screen_x))
				* TEX / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && x > 0 && x < WIDTH
			&& spr->transform_y < data->z_buffer[x])
			sprites_y_loop(data, spr, tmp, x);
	}
}

void	sprites_handle(t_data *data)
{
	t_anim		*tmp;
	t_sprites	spr;

	sprites_calc_dist(data);
	tmp = data->anims;
	while (tmp)
	{
		spr.sprite_x = tmp->x - data->p.x;
		spr.sprite_y = tmp->y - data->p.y;
		sprites_start_end(data, &spr);
		sprites_x_loop(data, &spr, tmp);
		--tmp->stage;
		if (tmp->stage == 0)
			tmp->stage = 150;
		tmp = tmp->next;
	}
}
