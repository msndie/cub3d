/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:06:42 by sclam             #+#    #+#             */
/*   Updated: 2021/11/08 15:16:24 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (s2[0] == '\0')
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
	free(s1);
	return (dest);
}

static char	*ft_rec(char *str)
{
	static size_t	i = 0;
	static size_t	stop = 0;
	char			*s;
	size_t			n;

	n = i;
	if (i >= ft_strlen(str) && stop == 0)
	{
		free(str);
		stop += 1;
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i += 1;
			break ;
		}
		i += 1;
	}
	s = ft_substr(str, n, i - n);
	return (s);
}

static void	*ft_clear_line(char *s)
{
	free(s);
	return (0);
}

static char	*ft_full_line(char *s, char *s1, int *ret, int fd)
{
	while (*ret > 0)
	{
		s[*ret] = '\0';
		s1 = ft_strjoin_gnl(s1, s);
		*ret = read(fd, s, BUFFER_SIZE);
	}
	free(s);
	return (s1);
}

char	*get_next_line(int fd)
{
	char			*s;
	static char		*s1 = NULL;
	int				ret;

	if (!s1)
	{
		s = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!s)
			return (0);
		ret = read(fd, s, BUFFER_SIZE);
		if (ret <= 0)
			return (ft_clear_line(s));
		s1 = ft_full_line(s, s1, &ret, fd);
		if (ret < 0)
		{
			s1 = ft_clear_line(s1);
			return (s1);
		}
	}
	return (ft_rec(s1));
}
