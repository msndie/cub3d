/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:48:12 by sclam             #+#    #+#             */
/*   Updated: 2022/05/06 17:18:11 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "./mlx/mlx.h"
# include <math.h>

#define MAP_TILE 4
#define PLAYER 2
#define WALL 1
#define EMPTY 0
#define SPACE -1
#define A 0
#define D 2
#define W 13
#define S 1
#define LEFT 123
#define RIGHT 124
#define WIDTH 1920
#define HEIGHT 1080
#define TEX_W 64
#define TEX_H 64

typedef struct s_point
{
	double	x;
	double	y;
} t_point;


typedef struct s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	t;
	int				trgb;
} t_colour;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
} t_img;

typedef struct s_info
{
	char		**map;
	int			**int_map;
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;
	t_colour	*f;
	t_colour	*c;
	int			width;
	int			height;
} t_info;



typedef struct s_mlx
{
	void	*mlx;
	void	*win;
} t_mlx;

typedef	struct s_rays
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_rays;


typedef struct s_data {
	char	**file;
	t_info	info;
	t_mlx	mlx;
	t_img	map;
	t_img	player;
	t_img	img;
	t_point	p;
	t_rays	rays;
} t_data;

int		check_walls(t_data *data);
int		map_checker(t_data *data);
int		parse_colour(char *str, char flag, t_data *data);
void	init_map(char *argv, t_data *data);
int		error(char *str);
void	free_all(t_data *data);
int		ft_in_set(char c, char const *set);
int		create_trgb(int t, int r, int g, int b);
void	cub_extension(char *argv);
void	null_init(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_square(t_img *img, int size, int colour, int out_colour, t_point p);
void	draw_line(t_img *img, int colour, t_point f, t_point t);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
void	map_to_int(t_data *data);

#endif /*CUBE3D_H*/