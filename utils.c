/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:15:19 by aserrano          #+#    #+#             */
/*   Updated: 2020/06/27 13:44:29 by marvin           ###   ########.fr       */
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

/*void	adjacent_spa(t_data *data, int l, int c)
{
	int		n;
	int		len;

	n = 0;
	if (data->map[l][c - 1] >= 0 && data->map[l][c - 1] == ' ')
		n++;
	else if (c + 1 < data->c < len && data->map[l][c + 1] == ' ')
		n++;
	else if (data->map[l - 1][c] >= 0 && data->map[l - 1][c] == ' ')
		n++;
	else if (l + 1 < data->l && data->map[l + 1][c] == ' ')
		n++;
	if (n > 0)
		data->map2[l][c] = '1';
	else
		data->map2[l][c] = '0';
}*/

/* This function returns the degree of a vertex in a graph (map)
** where 1 means it is connected to another vertex */

int		deg_vtx(char **map, int l, int c)
{
	int	d;

	d = 0;
	if (map[l - 1][c] && map[l - 1][c] == 1)
		d++;
	if (map[l + 1][c] && map[l + 1][c] == 1)
		d++;
	if (map[l][c - 1] && map[l][c - 1] == 1)
		d++;
	if (map[l][c + 1] && map[l][c + 1] == 1)
		d++;
	return (d);
}

void	check_one(t_data *data, int l, int c)
{
	if (deg_vtx(data->map, l, c) < 2)
	{
		data->map2[l][c] = '0';
		if (data->map[l - 1][c] && data->map[l - 1][c] == 1)
			check_one(data, l - 1, c);
		if (data->map[l + 1][c] && data->map[l + 1][c] == 1)
			check_one(data, l + 1, c);
		if (data->map[l][c - 1] && data->map[l][c - 1] == 1)
			check_one(data, l, c - 1);
		if (data->map[l][c + 1] && data->map[l][c + 1] == 1)
			check_one(data, l, c + 1);
	}
}

int		find_ones(t_data *data)
{
	int l;
	int c;

	l = 0;
	while (data->map2[l])
	{
		c = 0;
		while (data->map2[l][c])
		{
			if (data->map2[l][c] == '1')
				return (1);
			c++;
		}
		l++;
	}
	return (0);
}