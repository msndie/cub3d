/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:35:50 by sclam             #+#    #+#             */
/*   Updated: 2021/10/13 20:53:37 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*s2;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(""));
	while (*s1)
	{
		if (ft_strchr(set, *s1) == 0)
			break ;
		s1++;
	}
	len = ft_strlen((char *)s1);
	while (len--)
	{
		if (ft_strrchr(set, s1[len]) == 0)
			break ;
	}
	s2 = ft_substr((char *)s1, 0, len + 1);
	return (s2);
}
