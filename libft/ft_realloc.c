/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:34:27 by sclam             #+#    #+#             */
/*   Updated: 2021/11/10 17:25:01 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*dst;

	if (!ptr)
		return (NULL);
	dst = malloc(size);
	if (!dst)
	{
		free(ptr);
		return (NULL);
	}
	ft_memmove(dst, ptr, size);
	free(ptr);
	return (dst);
}
