/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:34:15 by sclam             #+#    #+#             */
/*   Updated: 2021/10/11 12:34:16 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr;
	const unsigned char	*ptr1;
	size_t				i;

	i = 0;
	ptr = (unsigned char *)dst;
	ptr1 = (unsigned char *)src;
	if (ptr1 < ptr)
	{
		while (++i <= len && src != dst)
			ptr[len - i] = ptr1[len - i];
	}
	else
		while (i++ < len && src != dst)
			*(ptr++) = *(ptr1++);
	return (dst);
}
