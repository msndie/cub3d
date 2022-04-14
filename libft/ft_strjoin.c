/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:06 by sclam             #+#    #+#             */
/*   Updated: 2021/10/11 12:35:06 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2 || s2[0] == '\0')
		return (ft_strdup(s1));
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (0);
	while (s2[n] != '\0')
	{
		while (s1[j] != '\0')
			dest[i++] = s1[j++];
		dest[i++] = s2[n++];
	}
	dest[i] = '\0';
	return (dest);
}
