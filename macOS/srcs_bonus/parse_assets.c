/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:12 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:34:07 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static t_img	*asset(t_data *data, char *str)
{
	t_img	*img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(data->mlx.mlx, str, &img->w, &img->h);
	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	if (img->w != 64 || img->h != 64)
	{
		mlx_destroy_image(data->mlx.mlx, img->img);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits,
			&img->line_length, &img->endian);
	return (img);
}

static int	compare_identifiers(char **strs, t_data *data)
{
	if (!ft_strncmp("NO", strs[0], 3) && !data->info.no)
		data->info.no = asset(data, strs[1]);
	else if (!ft_strncmp("SO", strs[0], 3) && !data->info.so)
		data->info.so = asset(data, strs[1]);
	else if (!ft_strncmp("WE", strs[0], 3) && !data->info.we)
		data->info.we = asset(data, strs[1]);
	else if (!ft_strncmp("EA", strs[0], 3) && !data->info.ea)
		data->info.ea = asset(data, strs[1]);
	else if (!ft_strncmp("DR", strs[0], 3) && !data->info.dr)
		data->info.dr = asset(data, strs[1]);
	else if (!ft_strncmp("DW", strs[0], 3) && !data->info.dr_wall)
		data->info.dr_wall = asset(data, strs[1]);
	else if (!ft_strncmp("H1", strs[0], 3) && !data->info.anim_first)
		data->info.anim_first = asset(data, strs[1]);
	else if (!ft_strncmp("H2", strs[0], 3) && !data->info.anim_second)
		data->info.anim_second = asset(data, strs[1]);
	else if (!ft_strncmp("H3", strs[0], 3) && !data->info.anim_third)
		data->info.anim_third = asset(data, strs[1]);
	else if (!ft_strncmp("F", strs[0], 2) && !data->info.f)
		data->info.f = parse_colour(strs[1]);
	else if (!ft_strncmp("C", strs[0], 2) && !data->info.c)
		data->info.c = parse_colour(strs[1]);
	else
		return (1);
	return (0);
}

int	type_id(t_data *data, char *str)
{
	char	**strs;
	int		ret;

	strs = ft_split(str, ' ');
	ret = 0;
	if (strs == NULL)
		ret = 2;
	else if (ft_char_arr_len(strs) < 2 || ft_char_arr_len(strs) > 2)
		ret = 1;
	else if (compare_identifiers(strs, data))
		ret = 1;
	ft_free_arr((void **)strs);
	return (ret);
}
