/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:40 by sclam             #+#    #+#             */
/*   Updated: 2021/10/12 17:38:23 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		n;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		n = 1;
		if (needle[0] == haystack[i])
		{
			while (needle[n] && haystack[i + n] == needle[n] && n + i < len)
				n++;
			if (needle[n] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
