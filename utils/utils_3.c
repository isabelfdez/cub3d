/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:07:45 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 19:08:49 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function returns the degree of a vertex in a graph (map)
** where 1 means it is connected to another vertex 
*/

int		deg_vtx(t_data *data, int l, int c)
{
	int	d;

	d = 0;
	if (l > 0 && data->map2[l - 1][c] == '1')
		d++;
	if (l < data->l - 1 && data->map2[l + 1][c] == '1')
		d++;
	if (c > 0 && data->map2[l][c - 1] == '1')
		d++;
	if (c < data->c - 1 && data->map2[l][c + 1] == '1')
		d++;
	return (d);
}

void	check_one(t_data *data, int l, int c)
{
	if (deg_vtx(data, l, c) < 2)
	{
		data->map2[l][c] = '0';
		if (l > 0 && data->map2[l - 1][c] == '1')
			check_one(data, l - 1, c);
		else if (l < data->l - 1 && data->map2[l + 1][c] == '1')
			check_one(data, l + 1, c);
		else if (c > 0 && data->map2[l][c - 1] == '1')
			check_one(data, l, c - 1);
		else if (c < data->c - 1 && data->map2[l][c + 1] == '1')
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

int		line_character(t_data *data)
{
	int		l;
	int		c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			if (ft_isalpha(data->map[l][c]))
				return (l);
			c++;
		}
		l++;
	}
	return (0);
}

int		col_character(t_data *data)
{
	int		l;
	int		c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			if (ft_isalpha(data->map[l][c]))
				return (c);
			c++;
		}
		l++;
	}
	return (0);
}
