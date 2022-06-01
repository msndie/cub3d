/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:29:25 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 14:07:11 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static void	find_pos(t_data *data, char c, int i, int j)
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

static void	height_and_maxlen(t_data *data)
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

static void	char_to_int_representation(char c, t_data *data, int i, int j)
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
