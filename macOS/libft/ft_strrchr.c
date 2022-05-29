/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:45 by sclam             #+#    #+#             */
/*   Updated: 2021/11/05 13:25:51 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;

	ptr = s;
	while (c > 256)
	{
		if (c > 256)
			c -= 256;
	}
	while (*s)
		s++;
	while (s != ptr)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	if (s == ptr && *s == c)
		return ((char *)s);
	return (0);
}
