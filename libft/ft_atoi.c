/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmine <yasmine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:12:52 by emencova          #+#    #+#             */
/*   Updated: 2024/11/01 12:10:12 by yasmine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/cub3d.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 9)
		|| (nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			printf("Error:\n"COLOR_RANGE"\n");
			exit (1);
		}
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') || nptr[i] == ',')
	{
		if (nptr[i] == ',')
			i++;
		else
		{
			res = res * 10 + (nptr[i] - '0');
			i++;
		}
	}
	return (res);
}

