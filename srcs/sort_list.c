/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:31:23 by sclam             #+#    #+#             */
/*   Updated: 2022/05/29 18:57:19 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_left_right(t_anim **left, t_anim **right, t_anim *anim)
{
	t_anim	*tmp;

	tmp = anim;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	*(left) = anim;
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

void	ft_merge_sort_list(t_anim **anims)
{
	t_anim	*tmp;
	t_anim	*left;
	t_anim	*right;

	tmp = *(anims);
	if (!tmp || !tmp->next)
		return ;
	ft_left_right(&left, &right, tmp);
	ft_merge_sort_list(&left);
	ft_merge_sort_list(&right);
	*(anims) = ft_sorted_merge(left, right);
}
