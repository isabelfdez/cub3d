/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:20:00 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/30 19:32:04 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*case_zero(char *str)
{
	if (!(str = malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = '0';
	str[1] = 0;
	return (str);
}

static char	*ft_itoa2(char *str, long int *i, int n, unsigned int n2)
{
	while (n2 / i[0] != 0)
	{
		i[0] = i[0] * 10;
		i[1]++;
	}
	if (!(str = malloc(sizeof(char) * i[1] + 1)))
		return (NULL);
	i[1] = 0;
	if (n < 0)
	{
		str[i[1]] = '-';
		i[1]++;
	}
	while (i[0] >= 10)
	{
		str[i[1]] = (n2 % i[0]) / (i[0] / 10) + '0';
		i[1]++;
		i[0] = i[0] / 10;
	}
	str[i[1]] = 0;
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	long int		i[2];
	unsigned int	n2;

	i[0] = 1;
	i[1] = 0;
	str = NULL;
	if (n == 0)
		str = case_zero(str);
	else
	{
		if (n < 0)
		{
			i[1]++;
			n2 = n * (-1);
		}
		else
			n2 = n;
		str = ft_itoa2(str, i, n, n2);
	}
	return (str);
}
