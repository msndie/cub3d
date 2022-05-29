/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:11 by sclam             #+#    #+#             */
/*   Updated: 2021/10/12 14:41:13 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lend;
	size_t	i;
	size_t	n;

	lend = ft_strlen(dst);
	n = ft_strlen(src);
	i = 0;
	if (dstsize <= lend)
		return (n + dstsize);
	else
		n += lend;
	while (lend + 1 < dstsize && src[i])
		dst[lend++] = src[i++];
	dst[lend] = '\0';
	return (n);
}
