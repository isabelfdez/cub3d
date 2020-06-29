/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserrano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 13:27:31 by isfernan          #+#    #+#             */
/*   Updated: 2020/05/03 13:01:50 by aserrano         ###   ########.fr       */
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
	while (aux[jcpy[1]] == ' ' || ft_isdigit(aux[jcpy[1]]))
		jcpy[1]++;
	data->map = (char **)malloc(sizeof(char *) * (lines + 1));
	data->map[lines] = NULL;
	while (--lines >= 0)
		*(data->map + lines) = (char *)(malloc)(sizeof(char) * (jcpy[1] - j) + 1);
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
		/*if (aux[jcpy[0]] == '\n')
		{
			data->map[l][c] = aux[jcpy[0]];
			c++;
			jcpy[0]++;
		}*/
		jcpy[0]++;
		data->map[l][c] = '\0';
		l++;
	}
	free(aux);
	check_map_content(data);
	check_map_closed(data);
	/*int		i = 0;
	while (i < l)
	{	
		printf("%s\n", data->map[i]);
		i++;
	}*/
}

/* This function checks that all the components of the map
** are numbers between 0 and 2, except for the character
** that indicates the position, which must be either
** N, S, E or W (it also checks that there is only one
** position character) */

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
				n--;
				c++;
			}
			else
			{
				ft_putstr_fd("Error\nInvalid map", 2);
				exit(EXIT_FAILURE);
			}	
		}
		l++;
	}
}

void	check_map_closed(t_data *data)
{
	int		l;
	int		*n;

	l = 0;
	n = malloc(sizeof(int) * ft_strlen(data->map[0]));
	set_zeros(n, (int)ft_strlen(data->map[0]));
	if (!(try_map(data->map, l, n))) /* Aquí deberíamos salir si el mapa es válido */
	{
		ft_putstr_fd("Error\nMap not closed", 2);
		exit(EXIT_FAILURE);
	}
}
/* Esta debería devolver el número de la última línea 
** u otra cosa en caso de que el mapa sea válido */
int		try_map(char **map, int l, int *n)
{
	int		*n2;

	n2 = malloc(sizeof(int) * ft_strlen(map[0]));
	while (map[l + 1])
	{
		set_ones(n, map[l]);
		set_ones(n2, map[l + 1]);
		if (!(compare_lines(n, n2, (int)ft_strlen(map[0]))))
			return (0);
		l++;
		/* Tendremos que comprobar aparte la última fila */
	}
	return (1);
}

int		compare_lines(int *n, int *n2, int j)
{
	int		i;

	i = 0;
	while (i < j)
	{
		if (n[i] == n2[i])
			i++;
		else if (n[i] == 1 && n2[i] == 0)
		{
			if ((adjacent_ones(n, i)) < 2)
				return (0);
		}
		i++;
	}
	return (1);
}

/*void	check_map_closed(t_data *data)
{
	int		l;
	int		c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			while(data->map[l][c] == '1')
				c++;
			if (data->map[l][c]) Si entramos aquí es porque hay un 0, un 2, un espacio o una letra
			{
				check_projections(data, l, c);
				c++;
			}
		}
	}
}*/

/* This set of functions checks that there are at least two 1's 
** in each line and column. It also checks that they have at 
** least two adjacent 1's */

/*void	check_projections_l(t_data *data)
{
	int		l[2];
	int		n;
	int		*c;

	l[0] = 0;
	c = malloc(sizeof(int) * 2);
	while (data->map[l[0]])
	{
		
		if (data->map[l[0]])
		{
			l[1] = max_map(data, l[0]);
			if ((l[1] - l[0]) > 1) Con esto sabemos que por lo menos hay 3 filas 
			{
				max_cols(c, l, data);
			}
		}
		else
		{
			ft_putstr_fd("Error\nInvalid map", 2);
			exit(EXIT_FAILURE);
		}
		
	}
}*/

/* This function returns the coordidates of the camera
** in the map */

/*void	search_camera(t_data *data, int *c_x, int *c_y)
{
	if (c_x = malloc(sizeof(int)));

}*/

/*int		number_walls(t_data *data, int l)
{
	int		c;
	int		n;

	c = 0;
	n = 0;
	while(data->map[l][c])
	{
		if (data->map[l][c] == '1')
			n++;
		c++;
	}
	return (n);
}

void	number_walls2(int **c, int l[], t_data *data)
{
	int		line;

	line = l[0];
	while (line <= l[1])
	{
		if ()
	}
}

int		max_map(t_data *data, int l)
{
	while (number_walls(data, l) >= 2)
		l++;
	return (l - 1);
}

void	max_cols(int **c, int l[], t_data *data)
{
	while ()
}*/
