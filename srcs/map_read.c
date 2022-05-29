/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:14:37 by sclam             #+#    #+#             */
/*   Updated: 2022/05/29 18:29:20 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_colour(char *str, char flag, t_data *data)
{
	char		**strs;
	int			var1;
	int			var2;
	t_colour	*p;

	var1 = 0;
	var2 = 0;
	while (str[var1])
	{
		if (!ft_in_set(str[var1], ",0123456789"))
			return (1);
		if (str[var1] == ',')
			++var2;
		++var1;
	}
	if (var2 > 2 || var2 < 2)
		return (1);
	strs = ft_split(str, ',');
	if (!strs)
		return (1);
	if (ft_char_arr_len(strs) != 3)
	{
		ft_free_arr((void **)strs);
		return (1);
	}
	p = (t_colour *)malloc(sizeof(t_colour));
	if (!p)
	{
		ft_free_arr((void **)strs);
		return (1);
	}
	var1 = 0;
	while (strs[var1])
	{
		var2 = ft_atoi(strs[var1]);
		if (var2 < 0 || var2 > 255)
		{
			free(p);
			ft_free_arr((void **)strs);
			return (1);
		}
		if (var1 == 0)
			p->r = var2;
		else if (var1 == 1)
			p->g = var2;
		else if (var1 == 2)
			p->b = var2;
		++var1;
	}
	p->t = 0;
	p->trgb = create_trgb(p->t, p->r, p->g, p->b);
	ft_free_arr((void **)strs);
	if (flag == 'f')
		data->info.f = p;
	else
		data->info.c = p;
	return (0);
}

int	find_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->p.x = -1;
	data->p.y = -1;
	while (data->info.map[i])
	{
		j = 0;
		while (data->info.map[i][j])
		{
			if (ft_in_set(data->info.map[i][j], "NSWE"))
			{
				if (data->p.x != -1 || data->p.y != -1)
					return (error("Map"));
				if (data->info.map[i][j] == 'N')
				{
					data->rays.plane_x = 0.66;
					data->rays.plane_y = 0.0;
					data->rays.dir_x = 0.0;
					data->rays.dir_y = -1.0;
				}
				else if (data->info.map[i][j] == 'S')
				{
					data->rays.plane_x = -0.66;
					data->rays.plane_y = 0.0;
					data->rays.dir_x = 0.0;
					data->rays.dir_y = 1.0;
				}
				else if (data->info.map[i][j] == 'W')
				{
					data->rays.plane_x = 0.0;
					data->rays.plane_y = -0.66;
					data->rays.dir_x = -1.0;
					data->rays.dir_y = 0.0;
				}
				else if (data->info.map[i][j] == 'E')
				{
					data->rays.plane_x = 0.0;
					data->rays.plane_y = 0.66;
					data->rays.dir_x = 1.0;
					data->rays.dir_y = 0.0;
				}
				data->p.x = j + 0.5;
				data->p.y = i + 0.5;
			}
			++j;
		}
		++i;
	}
	return (0);
}

void	map_to_int(t_data *data)
{
	size_t	max;
	int		i;
	int		j;

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
	i = 0;
	while (data->info.map[i])
	{
		j = 0;
		data->info.int_map[i] = (int *)malloc(sizeof(int) * max);
		if (!data->info.int_map[i])
		{
			ft_putendl_fd("Malloc error", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
		while (data->info.map[i][j])
		{
			if (data->info.map[i][j] == '1')
				data->info.int_map[i][j] = WALL;
			else if (ft_in_set(data->info.map[i][j], "0NSWEH"))
				data->info.int_map[i][j] = EMPTY;
			else if (data->info.map[i][j] == '4')
				data->info.int_map[i][j] = DOOR_CLOSED;
			else if (data->info.map[i][j] == ' ')
				data->info.int_map[i][j] = SPACE;
			++j;
		}
		while (j < (int)max)
			data->info.int_map[i][j++] = SPACE;
		++i;
	}
	data->info.int_map[i] = NULL;
}

void	init_map(char *argv, t_data *data)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = open(argv, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putendl_fd(" is a directory", 2);
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Open error", 2);
		exit(EXIT_FAILURE);
	}
	data->file = (char **)malloc(sizeof(char **));
	if (!data->file)
	{
		ft_putendl_fd("Malloc error", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	data->file[i] = get_next_line(fd);
	if (!data->file[i])
	{
		ft_putendl_fd("Malloc error", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	while (data->file[i])
	{
		data->file = ft_realloc(data->file, sizeof(char **) * (++i + 1));
		if (!data->file)
		{
			ft_putendl_fd("Malloc error", 2);
			close(fd);
			exit(EXIT_FAILURE);
		}
		data->file[i] = get_next_line(fd);
	}
	close(fd);
	if (map_checker(data))
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	if (find_pos(data))
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
}
