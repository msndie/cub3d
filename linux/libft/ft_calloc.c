/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:31:11 by sclam             #+#    #+#             */
/*   Updated: 2021/11/07 03:56:13 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size != 0 && (count * size) / size != count)
		return (0);
	p = malloc(size * count);
	if (p == NULL)
		return (0);
	ft_bzero(p, count * size);
	return (p);
}
