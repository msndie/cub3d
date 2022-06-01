/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:44:50 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 13:45:09 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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
	if (p[i][j] == ' ' && (up != -1 && ft_in_set(p[up][j], "0NSWE")))
		return (1);
	if (p[i][j] == ' ' && (down != -1 && ft_in_set(p[down][j], "0NSWE")))
		return (1);
	if (ft_in_set(p[i][j], "0NSWE") && (up == -1 || down == -1))
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
	if (p[i][j] == ' ' && (left != -1 && ft_in_set(p[i][left], "0NSWE")))
		return (1);
	if (p[i][j] == ' ' && (right != -1 && ft_in_set(p[i][right], "0NSWE")))
		return (1);
	if (ft_in_set(p[i][j], "0NSWE") && (left == -1 || right == -1))
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
				|| !ft_in_set(data->info.map[i][j], " 10NSWE"))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
