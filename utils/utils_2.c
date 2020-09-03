/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:06:47 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 19:07:53 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find_camera(t_data *data, int l)
{
	int		c;

	c = 0;
	while (data->map[l][c])
	{
		if (map_letters(data->map[l][c]))
			return (1);
		c++;
	}
	return (0);
}

void	set_zeros(int *n, int l)
{
	int		i;

	i = 0;
	while (i < l)
	{
		n[i] = 0;
		i++;
	}
}

void	set_ones(int *n, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			n[i] = 1;
		i++;
	}
}

int		adjacent_ones(int *n, int j, int len)
{
	int		z;

	z = 0;
	if (j - 1 >= 0 && n[j - 1] == 1)
		z++;
	if (j + 1 < len && n[j + 1] == 1)
		z++;
	return (z);
}

int		adjacent_ones2(char **map, int l, int i)
{
	if (l - 1 >= 0 && map[l - 1][i] == '1')
		return (1);
	return (0);
}
