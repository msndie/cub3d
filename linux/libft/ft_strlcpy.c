/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:17 by sclam             #+#    #+#             */
/*   Updated: 2021/10/11 12:35:17 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	count;

	len = 0;
	count = ft_strlen(src);
	if (dstsize == 0)
		return (count);
	while (src[len] != '\0' && len < (dstsize - 1))
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (count);
}
