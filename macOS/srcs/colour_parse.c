/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:26:31 by sclam             #+#    #+#             */
/*   Updated: 2022/06/01 16:09:39 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static char	**parse_colour_helper(char *str)
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

static t_colour	*check_color(t_colour *p)
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
