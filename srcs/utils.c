/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:15:16 by sclam             #+#    #+#             */
/*   Updated: 2022/05/27 16:38:30 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

void	free_all(t_data *data)
{
	if (data->z_buffer)
		free(data->z_buffer);
	if (data->file)
		ft_free_arr((void **)data->file);
	if (data->info.map)
		free(data->info.map);
	if (data->info.c)
		free(data->info.c);
	if (data->info.f)
		free(data->info.f);
	if (data->info.ea)
		free(data->info.ea);
	if (data->info.no)
		free(data->info.no);
	if (data->info.so)
		free(data->info.so);
	if (data->info.we)
		free(data->info.we);
	if (data->info.int_map)
		ft_free_arr((void **)data->info.int_map);
	if (data->mlx.mlx)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->sonics)
		ft_free_lists(data->sonics);
}

int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (c);
		i++;
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void	null_init(t_data *data)
{
	data->file = NULL;
	data->info.c = NULL;
	data->info.f = NULL;
	data->info.no = NULL;
	data->info.ea = NULL;
	data->info.so = NULL;
	data->info.we = NULL;
	data->info.map = NULL;
	data->img.img = NULL;
	data->mlx.mlx = NULL;
	data->info.dr = NULL;
	data->z_buffer = NULL;
	data->info.sonic_first = NULL;
	data->info.sonic_second = NULL;
	data->info.sonic_third = NULL;
}
