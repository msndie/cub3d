/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:19:02 by sclam             #+#    #+#             */
/*   Updated: 2022/05/28 13:55:40 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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

int	ft_lst_size(t_anim *lst)
{
	int		i;
	t_anim	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
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

int	ft_lst_add_front(t_anim **lst, t_anim *new)
{
	if (!new)
		return (-1);
	new->next = *lst;
	*lst = new;
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

static void	ft_left_right(t_anim **left, t_anim **right, t_anim *sonics)
{
	t_anim	*tmp;

	tmp = sonics;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	*(left) = sonics;
	*(right) = tmp->next;
	tmp->next = NULL;
}

static t_anim	*ft_sorted_merge(t_anim *left, t_anim *right)
{
	t_anim	*res;

	if (!left)
		return (right);
	else if (!right)
		return (left);
	if (left->dist > right->dist)
	{
		res = left;
		res->next = ft_sorted_merge(left->next, right);
	}
	else
	{
		res = right;
		res->next = ft_sorted_merge(left, right->next);
	}
	return (res);
}

void	ft_merge_sort_list(t_anim **sonics)
{
	t_anim	*tmp;
	t_anim	*left;
	t_anim	*right;

	tmp = *(sonics);
	if (!tmp || !tmp->next)
		return ;
	ft_left_right(&left, &right, tmp);
	ft_merge_sort_list(&left);
	ft_merge_sort_list(&right);
	*(sonics) = ft_sorted_merge(left, right);
}
