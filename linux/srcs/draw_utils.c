/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:33:35 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:40:13 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, int size, int colour, int out_colour, t_point p)
{
	int	i;
	int	j;

	i = p.y;
	while (i < p.y + size)
	{
		j = p.x;
		while (j < p.x + size)
		{
			if (i == 0 || i == p.y + size - 1 || j == 0 || j == p.x + size - 1)
				my_mlx_pixel_put(img, j++, i, out_colour);
			else
				my_mlx_pixel_put(img, j++, i, colour);
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
