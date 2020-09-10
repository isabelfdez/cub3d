/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:14:44 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 16:41:03 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_character(t_data *data)
{
	int	l;
	int	c;

	l = line_character(data);
	c = col_character(data);
	if (!check_line_char(data))
		exit_program_data(data, 6);
	if (!check_col_char(data))
		exit_program_data(data, 6);
}

int		check_line_char(t_data *data)
{
	int c;
	int l2;
	int	j;

	c = 0;
	while (c < data->c)
	{
		l2 = 0;
		j = 0;
		while (l2 < data->l)
		{
			if (data->map2[l2][c] == '1')
				j++;
			l2++;
		}
		if (j < 2)
			return (0);
		c++;
	}
	return (1);
}

int		check_col_char(t_data *data)
{
	int l;
	int c2;
	int j;

	l = 0;
	while (l < data->l)
	{
		c2 = 0;
		j = 0;
		while (c2 < data->c)
		{
			if (data->map2[l][c2] == '1')
				j++;
			c2++;
		}
		if (j < 2)
			return (0);
		l++;
	}
	return (1);
}
