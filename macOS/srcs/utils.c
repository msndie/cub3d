/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:15:16 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 15:01:35 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

void	free_all(t_data *data)
{
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
	if (data->dda)
		free(data->dda);
}

void	null_init(t_data *data)
{
	ft_memset(&data->info, 0, sizeof(t_info));
	ft_memset(&data->rays, 0, sizeof(t_rays));
	ft_memset(&data->keys, 0, sizeof(t_keys));
	data->file = NULL;
	data->img.img = NULL;
	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->dda = NULL;
	data->p.x = -1;
	data->p.y = -1;
}
