/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:15:19 by aserrano          #+#    #+#             */
/*   Updated: 2020/07/08 15:43:33 by isfernan         ###   ########.fr       */
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

t_dvector	create_dvec(double i, double j)
{
	t_dvector	vector;

	vector.x = i;
	vector.y = j;
	return (vector);
}

t_ivector	create_ivec(int i, int j)
{
	t_ivector	vector;

	vector.x = i;
	vector.y = j;
	return (vector);
}

void	initialize_keys(t_data *data)
{
	data->key.backwards = 0;
	data->key.towards = 0;
	data->key.right = 0;
	data->key.left = 0;
	data->key.arrow_left = 0;
	data->key.arrow_right = 0;
	data->key.esc = 0;
	data->old_time = 0;
	data->time = 0;
}

/*void	print_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->l)
	{
		j = 0;
		while (j < data->c)
		{
			printf("%c", data->map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}*/

void	print_map(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->l)
	{
		ft_putendl_fd(data->map[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int		find_key_pressed(t_data *data)
{
	int n;

	n = 0;
	if (data->key.towards == 1)
		n++;
	if (data->key.backwards == 1)
		n++;
	if (data->key.right == 1)
		n++;
	if (data->key.left == 1)
		n++;
	if (data->key.arrow_left == 1)
		n++;
	if (data->key.arrow_right == 1)
		n++;
	return (n);
}
