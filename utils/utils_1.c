/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:15:19 by aserrano          #+#    #+#             */
/*   Updated: 2020/09/03 19:07:17 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int		skip_spa_com(char *str, int i)
{
	while (str[i] == ' ' || str[i] == ',')
		i++;
	return (i);
}

/* This function counts the amount of c-characters
** that appear in str starting the count from index j */

int		count_from(char c, char *str, int j)
{
	int		n;

	n = 0;
	while (str[j])
	{
		if (str[j] == c)
			n++;
		j++;
	}
	return (n);
}

int		map_numbers_spa(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		return (1);
	return (0);
}

int		map_letters(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
