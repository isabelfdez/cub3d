/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:19:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 17:02:20 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		nb;

	i = 0;
	neg = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		nb = nb * (-1);
	return (nb);
}

/*
** This function converts a string to a float
*/

float		ft_atof(const char *aux, int i)
{
	float	nb;

	nb = (float)ft_atoi(aux + i);
	while (ft_isdigit(aux[i]))
		i++;
	if (aux[i] == '.' && nb >= 0)
		nb = nb + ((ft_atoi(aux + i + 1)) /
		(pow(10.0, count_nb(ft_atoi(aux + i + 1)))));
	else if (aux[i] == '.' && nb < 0)
		nb = nb - ((ft_atoi(aux + i + 1)) /
		(pow(10.0, count_nb(ft_atoi(aux + i + 1)))));
	return (nb);
}
