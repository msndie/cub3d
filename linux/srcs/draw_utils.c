/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:33:35 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 15:13:37 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_tex_colour(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (4 * TEX * y) + (4 * x)));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_square *sq)
{
	int	i;
	int	j;

	i = sq->p.y;
	while (i < sq->p.y + sq->size)
	{
		j = sq->p.x;
		while (j < sq->p.x + sq->size)
		{
			if (i == 0 || i == sq->p.y + sq->size - 1 || j == 0
				|| j == sq->p.x + sq->size - 1)
				my_mlx_pixel_put(sq->img, j++, i, sq->out_colour);
			else
				my_mlx_pixel_put(sq->img, j++, i, sq->colour);
		}
		++i;
	}
}

void	draw_line(t_img *img, int colour, t_point f, t_point t)
{
	double	x;
	double	y;
	double	max;
	double	n;

	x = t.x - f.x;
	y = t.y - f.y;
	max = fmax(fabs(x), fabs(y));
	x /= max;
	y /= max;
	n = 0;
	while (n < max)
	{
		my_mlx_pixel_put(img, f.x, f.y, colour);
		f.x += x;
		f.y += y;
		++n;
	}
}
