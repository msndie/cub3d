/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:07:39 by sclam             #+#    #+#             */
/*   Updated: 2021/10/12 20:39:45 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(int n)
{
	size_t	count;

	count = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_rec(int n, char *s, int i)
{
	int	j;

	j = 0;
	while (n > 0)
	{
		j = n % 10;
		s[i--] = j + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		m;
	size_t	i;

	m = 0;
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		m += -1;
		n = -n;
		i++;
	}
	i += ft_count(n);
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	s[i--] = '\0';
	ft_rec(n, s, i);
	if (m < 0)
		s[0] = '-';
	return (s);
}
