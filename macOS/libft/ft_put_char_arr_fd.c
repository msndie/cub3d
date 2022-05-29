/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_char_arr_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:20:05 by sclam             #+#    #+#             */
/*   Updated: 2022/03/13 16:34:37 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_char_arr_fd(char **arr, int fd)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			ft_putstr_fd(arr[i], fd);
			i++;
		}
	}
}
