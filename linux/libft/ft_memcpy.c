/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:34:10 by sclam             #+#    #+#             */
/*   Updated: 2021/10/11 12:34:10 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr1;
	size_t				i;

	i = 0;
	ptr = (unsigned char *)dst;
	ptr1 = (unsigned char *)src;
	while (i++ < n && dst != src)
		*(ptr++) = *(ptr1++);
	return (dst);
}
