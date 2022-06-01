/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:14:45 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 15:16:21 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static int	is_full_info(t_info *info)
{
	if (info->c && info->ea && info->f && info->no && info->so && info->we)
		return (1);
	return (0);
}

static int	check_line(char *str)
{
	int	i;
	int	spaces;
	int	sym;

	i = 0;
	spaces = 0;
	sym = 0;
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			++spaces;
		else if (str[i] != '\n')
			++sym;
		i++;
	}
	if (spaces >= 0 && sym == 0)
		return (1);
	return (0);
}

static int	map_assignment(t_data *data, int start)
{
	int	i;

	i = start;
	while (data->file[i])
	{
		if (!ft_strncmp("\n", data->file[i], 2) || check_line(data->file[i]))
			return (error("Map"));
		++i;
	}
	data->info.map = (char **)malloc(sizeof(char *) * (i - start + 1));
	if (!data->info.map)
		return (error("Malloc"));
	i = 0;
	while (data->file[start])
	{
		if (data->file[start][ft_strlen(data->file[start]) - 1] == '\n')
			data->file[start][ft_strlen(data->file[start]) - 1] = '\0';
		data->info.map[i++] = data->file[start++];
	}
	data->info.map[i] = NULL;
	return (0);
}

int	map_checker(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (data->file[i])
	{
		if (ft_strncmp("\n", data->file[i], 2) != 0)
		{
			if (check_line(data->file[i]))
				return (error("Map"));
			if (is_full_info(&data->info))
				break ;
			if (data->file[i][ft_strlen(data->file[i]) - 1] == '\n')
				data->file[i][ft_strlen(data->file[i]) - 1] = '\0';
			ret = type_id(data, data->file[i]);
			if (ret == 2)
				return (error("Malloc"));
			if (ret == 1)
				return (error("Map"));
		}
		++i;
	}
	if (!data->file[i])
		return (error("Map"));
	return (map_assignment(data, i));
}

void	cub_extension(char *argv)
{
	size_t	i;

	i = ft_strlen(argv);
	if (ft_strncmp(argv + (i - 4), ".cub", 4) == 0 && i - 4 != 0)
		return ;
	ft_putendl_fd("Wrong extension", 2);
	exit(EXIT_FAILURE);
}
