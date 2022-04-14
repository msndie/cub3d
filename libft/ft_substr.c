/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:55 by sclam             #+#    #+#             */
/*   Updated: 2021/10/11 12:35:55 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*dest;

	count = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	while (count < len)
		dest[count++] = s[start++];
	dest[count] = '\0';
	return (dest);
}
