/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:14:37 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 14:39:11 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

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
	else if (c == 'e')
		ft_putendl_fd("Error\nMalloc error or empty file", 2);
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
		error_exit('e', NULL, data, fd);
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
