/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:14:37 by sclam             #+#    #+#             */
/*   Updated: 2022/05/30 19:54:17 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**parse_colour_helper(char *str)
{
	int		var1;
	int		var2;
	char	**strs;

	var1 = 0;
	var2 = 0;
	while (str[var1])
	{
		if (!ft_in_set(str[var1], ",0123456789"))
			return (NULL);
		if (str[var1] == ',')
			++var2;
		++var1;
	}
	if (var2 > 2 || var2 < 2)
		return (NULL);
	strs = ft_split(str, ',');
	if (!strs)
		return (NULL);
	if (ft_char_arr_len(strs) != 3)
	{
		ft_free_arr((void **)strs);
		return (NULL);
	}
	return (strs);
}

t_colour	*check_color(t_colour *p)
{
	p->t = 0;
	if (p->r < 0 || p->r > 255 || p->g < 0
		|| p->g > 255 || p->b < 0 || p->b > 255)
	{
		free(p);
		return (NULL);
	}
	p->trgb = create_trgb(0, p->r, p->g, p->b);
	return (p);
}

t_colour	*parse_colour(char *str)
{
	char		**strs;
	int			var1;
	int			var2;
	t_colour	*p;

	strs = parse_colour_helper(str);
	if (!strs)
		return (NULL);
	p = (t_colour *)malloc(sizeof(t_colour));
	if (!p)
		return (ft_free_arr((void **)strs));
	var1 = -1;
	while (strs[++var1])
	{
		var2 = ft_atoi(strs[var1]);
		if (var1 == 0)
			p->r = var2;
		else if (var1 == 1)
			p->g = var2;
		else if (var1 == 2)
			p->b = var2;
	}
	ft_free_arr((void **)strs);
	return (check_color(p));
}

void	find_pos(t_data *data, char c, int i, int j)
{
	if (c == 'N')
	{
		data->rays.plane_x = 0.66;
		data->rays.dir_y = -1.0;
	}
	else if (c == 'S')
	{
		data->rays.plane_x = -0.66;
		data->rays.dir_y = 1.0;
	}
	else if (c == 'W')
	{
		data->rays.plane_y = -0.66;
		data->rays.dir_x = -1.0;
	}
	else if (c == 'E')
	{
		data->rays.plane_y = 0.66;
		data->rays.dir_x = 1.0;
	}
	data->p.x = j + 0.5;
	data->p.y = i + 0.5;
}

void	height_and_maxlen(t_data *data)
{
	size_t	max;
	int		i;

	max = 0;
	i = 0;
	while (data->info.map[i])
	{
		if (ft_strlen(data->info.map[i]) > max)
			max = ft_strlen(data->info.map[i]);
		++i;
	}
	data->info.int_map = (int **)malloc(sizeof(int *) * (i + 1));
	if (!data->info.int_map)
	{
		ft_putendl_fd("Malloc error", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	data->info.height = i;
	data->info.width = (int)max;
}

void	char_to_int_representation(char c, t_data *data, int i, int j)
{
	if (ft_in_set(c, "NSWE"))
	{
		if (data->p.x != -1 || data->p.y != -1)
		{
			ft_putendl_fd("Error", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		find_pos(data, c, i, j);
	}
	if (c == '1')
		data->info.int_map[i][j] = WALL;
	else if (ft_in_set(c, "0NSWEH"))
		data->info.int_map[i][j] = EMPTY;
	else if (c == '4')
		data->info.int_map[i][j] = DOOR_CLOSED;
	else if (c == ' ')
		data->info.int_map[i][j] = SPACE;
}

void	map_to_int(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	height_and_maxlen(data);
	while (data->info.map[i])
	{
		j = -1;
		data->info.int_map[i] = (int *)malloc(sizeof(int) * data->info.width);
		if (!data->info.int_map[i])
		{
			ft_putendl_fd("Malloc error", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		while (data->info.map[i][++j])
			char_to_int_representation(data->info.map[i][j], data, i, j);
		while (j < data->info.width)
			data->info.int_map[i][j++] = SPACE;
		++i;
	}
	data->info.int_map[i] = NULL;
}

static void	error_exit(char c, char *str, t_data *data, int fd)
{
	if (c == 'd')
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
	}
	else if (c == 'o')
		perror("open");
	else if (c == 'm')
		perror("malloc");
	if (fd > 0)
		close(fd);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	exit(EXIT_FAILURE);
}

static void	read_file(t_data *data, int fd)
{
	size_t	i;

	i = 0;
	data->file[i] = get_next_line(fd);
	if (!data->file[i])
		error_exit('m', NULL, data, fd);
	while (data->file[i])
	{
		data->file = ft_realloc(data->file, sizeof(char **) * (++i + 1));
		if (!data->file)
			error_exit('m', NULL, data, fd);
		data->file[i] = get_next_line(fd);
	}
}

void	init_map(char *argv, t_data *data)
{
	int		fd;

	fd = open(argv, O_DIRECTORY);
	if (fd != -1)
		error_exit('d', argv, data, fd);
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error_exit('o', NULL, data, fd);
	data->file = (char **)malloc(sizeof(char **));
	if (!data->file)
		error_exit('m', NULL, data, fd);
	read_file(data, fd);
	close(fd);
	if (map_checker(data))
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
}
