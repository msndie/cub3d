/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:19:02 by sclam             #+#    #+#             */
/*   Updated: 2022/05/29 22:51:12 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_anim	*ft_lst_new(int x, int y)
{
	t_anim	*tmp;

	tmp = malloc(sizeof(t_anim));
	if (tmp == NULL)
		return (0);
	tmp->next = NULL;
	tmp->x = x + 0.5;
	tmp->y = y + 0.5;
	return (tmp);
}

t_anim	*ft_lst_last(t_anim *lst)
{
	t_anim	*tmp;

	tmp = lst;
	while (lst && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	ft_lst_add_back(t_anim **lst, t_anim *new)
{
	t_anim	*tmp;

	if (!new)
		return (-1);
	if (!*lst)
	{
		*lst = new;
		return (0);
	}
	else
	{
		tmp = ft_lst_last(*lst);
		tmp->next = new;
	}
	return (0);
}

void	*ft_free_lists(t_anim *node)
{
	t_anim	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	node = NULL;
	return (NULL);
}

int	sprites_create(t_data *data)
{
	size_t	i;
	size_t	j;
	t_anim	*tmp;

	i = -1;
	while (++i < ft_char_arr_len(data->info.map))
	{
		j = -1;
		while (++j < ft_strlen(data->info.map[i]))
		{
			if (data->info.map[i][j] == 'H')
			{
				if (ft_lst_add_back(&data->anims, ft_lst_new(j, i)))
					return (1);
				tmp = ft_lst_last(data->anims);
				tmp->anim_first = data->info.anim_first;
				tmp->anim_second = data->info.anim_second;
				tmp->anim_third = data->info.anim_third;
				ft_lst_last(data->anims)->stage = 150;
			}	
		}
	}
	return (0);
}
