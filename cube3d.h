/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:48:12 by sclam             #+#    #+#             */
/*   Updated: 2022/05/28 20:03:03 by sclam            ###   ########.fr       */
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
#define DOOR_CLOSED 4
#define DOOR_OPENDED 3
#define WALL 1
#define EMPTY 0
#define SPACE -1
#define A 0
#define D 2
#define W 13
#define S 1
#define LEFT 123
#define RIGHT 124
#define TILDA 50
#define SPACEBAR 49
#define WIDTH 1860
#define HEIGHT 1024
#define TEX 64
#define MV_SPEED 0.08
#define ROT_SPEED 0.05

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
	int		bits;
	int		line_length;
	int		endian;
	int		h;
	int		w;
} t_img;

typedef struct s_anim
{
	double			x;
	double			y;
	double			dist;
	t_img			*anim_first;
	t_img			*anim_second;
	t_img			*anim_third;
	short			stage;
	struct s_anim	*next;
} t_anim;

typedef struct s_info
{
	char		**map;
	int			**int_map;
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;

	t_img		*dr;
	t_img		*anim_first;
	t_img		*anim_second;
	t_img		*anim_third;

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
	int		pitch;
} t_rays;

typedef struct s_keys
{
	short	w;
	short	s;
	short	a;
	short	d;
	short	left;
	short	right;
	short	tilda;
} t_keys;

typedef struct s_mouse
{
	int x;
	int y;
} t_mouse;

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
	double	doorx;
	double	wallyoffset;
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
	double	*z_buffer;
	t_anim	*anims;
	t_dda	*dda;
	t_info	info;
	t_mlx	mlx;
	t_img	map;
	t_img	player;
	t_img	img;
	t_point	p;
	t_rays	rays;
	t_keys	keys;
	t_mouse	mouse;
} t_data;

t_anim	*ft_lst_new(int x, int y);
int	ft_lst_size(t_anim *lst);
t_anim	*ft_lst_last(t_anim *lst);
int	ft_lst_add_back(t_anim **lst, t_anim *new);
int	ft_lst_add_front(t_anim **lst, t_anim *new);
void	*ft_free_lists(t_anim *node);
void	ft_merge_sort_list(t_anim **sonics);

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