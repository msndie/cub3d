/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:14:45 by sclam             #+#    #+#             */
/*   Updated: 2022/05/31 14:36:52 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d_bonus.h"

static int	is_full_info(t_info *info)
{
	if (info->c && info->ea && info->f && info->no && info->so && info->we
		&& info->dr && info->anim_first && info->anim_second
		&& info->anim_third && info->dr_wall)
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

t_img	*asset(t_data *data, char *str)
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

static int	type_id(t_data *data, char *str)
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

static int	check_up_down(t_data *data, int i, int j)
{
	char	**p;
	int		up;
	int		down;

	p = data->info.map;
	if (i - 1 < 0 || (int)ft_strlen(p[i - 1]) <= j)
		up = -1;
	else
		up = i - 1;
	if (i + 1 == (int)ft_char_arr_len(p) || (int)ft_strlen(p[i + 1]) <= j)
		down = -1;
	else
		down = i + 1;
	if (p[i][j] == ' ' && (up != -1 && ft_in_set(p[up][j], "40NSWEH")))
		return (1);
	if (p[i][j] == ' ' && (down != -1 && ft_in_set(p[down][j], "40NSWEH")))
		return (1);
	if (ft_in_set(p[i][j], "40NSWEH") && (up == -1 || down == -1))
		return (1);
	return (0);
}

static int	check_left_right(t_data *data, int i, int j)
{
	char	**p;
	int		left;
	int		right;

	p = data->info.map;
	if (j - 1 < 0)
		left = -1;
	else
		left = j - 1;
	if (j + 1 == (int)ft_strlen(p[i]))
		right = -1;
	else
		right = j + 1;
	if (p[i][j] == ' ' && (left != -1 && ft_in_set(p[i][left], "40NSWEH")))
		return (1);
	if (p[i][j] == ' ' && (right != -1 && ft_in_set(p[i][right], "40NSWEH")))
		return (1);
	if (ft_in_set(p[i][j], "40NSWEH") && (left == -1 || right == -1))
		return (1);
	return (0);
}

int	check_walls(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_char_arr_len(data->info.map))
	{
		j = 0;
		while (j < ft_strlen(data->info.map[i]))
		{
			if (check_left_right(data, i, j) || check_up_down(data, i, j)
				|| !ft_in_set(data->info.map[i][j], " 140NSWEH"))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}