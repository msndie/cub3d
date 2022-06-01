/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:48:12 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 16:21:54 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "../mlx/mlx.h"
# include <math.h>

# define MAP_TILE 4
# define WALL 1
# define EMPTY 0
# define SPACE -1
# define A 97
# define D 100
# define W 119
# define S 115
# define LEFT 65361
# define RIGHT 65363
# define WIDTH 1024
# define HEIGHT 720
# define TEX 64
# define MV_SPEED 0.08
# define ROT_SPEED 0.05

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	trgb;
}	t_colour;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits;
	int		line_length;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_square
{
	t_img	*img;
	int		size;
	int		colour;
	int		out_colour;
	t_point	p;
}	t_square;

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
}	t_info;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_rays
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		pitch;
}	t_rays;

typedef struct s_keys
{
	short	w;
	short	s;
	short	a;
	short	d;
	short	left;
	short	right;
}	t_keys;

typedef struct s_dda
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
	double	step;
	double	texpos;
	int		texx;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
}	t_dda;

typedef struct s_data {
	char	**file;
	t_dda	*dda;
	t_info	info;
	t_mlx	mlx;
	t_img	img;
	t_point	p;
	t_rays	rays;
	t_keys	keys;
}	t_data;

void		draw_square(t_square *sq);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_line(t_img *img, int colour, t_point f, t_point t);
void		draw_fc(t_data *data);
void		draw_loop(t_data *data, t_dda *dda, int x);
int			get_tex_colour(t_img *img, int x, int y);
int			create_trgb(int t, int r, int g, int b);

int			key_pressed(int keycode, t_data *data);
int			key_released(int keycode, t_data *data);
void		move_camera(t_data *data);

void		move_forvard(t_data *data);
void		move_back(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);
void		rotate_camera(t_data *data);

void		perform_dda(t_data *data, t_dda *dda);
void		main_raycast_loop(t_dda *dda, t_data *data);
int			loop_hook(t_data *data);

int			check_walls(t_data *data);
int			map_checker(t_data *data);
void		cub_extension(char *argv);

void		map_to_int(t_data *data);
void		init_map(char *argv, t_data *data);

t_colour	*parse_colour(char *str);
int			type_id(t_data *data, char *str);

int			error(char *str);
void		free_all(t_data *data);
void		null_init(t_data *data);

#endif /*CUB3D_H*/