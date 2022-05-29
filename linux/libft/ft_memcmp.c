/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:34:03 by sclam             #+#    #+#             */
/*   Updated: 2021/10/12 21:12:53 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr1;
	size_t			i;

	ptr = (unsigned char *)s1;
	ptr1 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i++ < n)
	{
		if (*ptr != *ptr1)
			return (*ptr - *ptr1);
		ptr++;
		ptr1++;
	}
	return (0);
}
