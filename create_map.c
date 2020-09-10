/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:11:29 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 16:27:13 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map(t_data *data, int j, char *aux)
{
	int		jcpy[2];
	int		lines;

	jcpy[0] = j;
	jcpy[1] = j;
	lines = count_from('\n', aux, j);
	data->l = lines;
	while (aux[jcpy[1]] == ' ' || ft_isalnum(aux[jcpy[1]]))
		jcpy[1]++;
	data->c = jcpy[1] - j;
	data->map = (char **)malloc(sizeof(char *) * (lines + 1));
	data->map2 = (char **)malloc(sizeof(char *) * (lines + 1));
	data->map[lines] = NULL;
	data->map2[lines] = NULL;
	while (--lines >= 0)
	{
		*(data->map + lines) = (char *)(malloc)(sizeof(char) *
			(jcpy[1] - j) + 1);
		*(data->map2 + lines) = (char *)(malloc)(sizeof(char) *
			(jcpy[1] - j) + 1);
	}
	fill_map(data, jcpy, aux);
}

void	fill_map(t_data *data, int jcpy[], char *aux)
{
	int		l;
	int		c;
	int		j;

	l = 0;
	j = jcpy[0];
	while (data->map[l])
	{
		c = 0;
		while (c < (jcpy[1] - j) && aux[jcpy[0]] != '\n')
		{
			data->map[l][c] = aux[jcpy[0]];
			c++;
			jcpy[0]++;
		}
		jcpy[0]++;
		data->map[l][c] = '\0';
		l++;
	}
	free(aux);
	alter_map(data);
	check_map_content(data);
	map_graph(data);
}

void	alter_map(t_data *data)
{
	int		l;
	int		c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			data->map2[l][c] = data->map[l][c];
			c++;
		}
		data->map2[l][c] = '\0';
		l++;
	}
	data->map2[l] = NULL;
}

/*
** This function checks that all the components of the map
** are numbers between 0 and 2, except for the character
** that indicates the position, which must be either
** N, S, E or W (it also checks that there is only one
** position character)
*/

void	check_map_content(t_data *data)
{
	int		c;
	int		l;
	int		n;

	l = 0;
	n = 1;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			if (map_numbers_spa(data->map[l][c]))
				c++;
			else if (map_letters(data->map[l][c]) && n == 1)
			{
				data->dir1 = data->map[l][c];
				n--;
				c++;
			}
			else
				exit_program_data(data, 5);
		}
		l++;
	}
}

/*
** j is the line and i the column
*/

void	map_graph(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				check_one(data, j, i);
			i++;
		}
		j++;
	}
	if (!find_ones(data))
	{
		ft_putstr_fd("Error\nInvalid map", 2);
		exit(EXIT_FAILURE);
	}
	check_character(data);
	count_sprites(data);
	start_raycasting(data);
}
