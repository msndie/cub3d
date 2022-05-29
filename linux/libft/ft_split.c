/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:23:33 by sclam             #+#    #+#             */
/*   Updated: 2021/10/14 20:26:20 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	while (*s == c && *s)
	{
		s++;
		i++;
	}
	return (i);
}

static char	*ft_strsrec(const char *s, char c)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (0);
	while (s[n] && n < i)
	{
		ptr[n] = s[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}

static void	*ft_free(char **strs, int n)
{
	while (n >= 0)
		free(strs[n--]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		n;

	i = -1;
	if (!s)
		return (0);
	n = ft_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (0);
	while (++i < n)
	{
		while (*s == c && *s)
			s++;
		strs[i] = ft_strsrec(s, c);
		if (!strs[i])
			return (ft_free(strs, n));
		s += ft_wordlen(s, c);
	}
	strs[i] = 0;
	return (strs);
}
