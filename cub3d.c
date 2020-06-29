/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:55:12 by marvin            #+#    #+#             */
/*   Updated: 2020/06/27 13:56:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Hay que ver que lines esté bien si añado saltos de línea al final */
/* El ft_atof está comentado porque no reconoce el pow */

int	main(int argc, char **argv)
{
	char    *file;
	int     fd;
	char	*str;
	char	*aux;
	char	*aux2;
	(void)	argc;

	file = argv[1];
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &str))
	{
		if (!aux)
			aux = ft_strdup(str);
		else
		{
			aux2 = ft_strjoin(aux, str);
			free(aux);
			aux = ft_strjoin(aux2, "\n");
			//aux = ft_strdup(aux2); 
			free(aux2);
		}
	}
	//printf("%s", aux);
	ft_readfile(aux);
}

void	ft_readfile(char *aux)
{
	t_data	*data;
	int		j;
	int		i;

	j = 0;
	i = 3;
	if (!(data = malloc(sizeof(t_data))))
		return ; /* Aquí hay que ver qué hacemos */
	while (i > 0) /* Si uno de los parámetros no está, no sale de aquí */
	{
		if (aux[j] == 'R')
		{
			j = ft_resolution(aux, j + 1, data);
			i--;
		}
		if (aux[j] == 'F')
		{
			j = ft_floorcol(aux, j + 1, data);
			i--;
		}
		if (aux[j] == 'C')
		{
			j = ft_ceilcol(aux, j + 1, data);
			i--;
		}
	}
	/* El parámetro j va a ser donde acaben los datos y empiece el mapa */
	allocate_map(data, j, aux);
	/*j = ft_strstr2(aux, "R");
	ft_resolution(aux, j + 1, data);
	j = ft_strstr2(aux, "F");
	ft_floorcol(aux, j + 1, data);
	j = ft_strstr2(aux, "C");
	ft_ceilcol(aux, j + 1, data);*/
}

int		ft_resolution(char *aux, int i, t_data *data)
{
	i = skip_spaces(aux, i);
	data->resx = ft_atoi(aux + i);
	while (ft_isdigit(aux[i]))
		i++;
	i = skip_spaces(aux, i);
	data->resy = ft_atoi(aux + i);
	while(ft_isdigit(aux[i]) || aux[i] == ' ' || aux[i] == '\n')
		i++;
	//printf("resx = %i, resy = %i\n", data->resx, data->resy);
	return (i);
}

int		ft_floorcol(char *aux, int i, t_data *data)
{
	i = skip_spaces(aux, i);
	data->floor.R = ft_atoi(aux + i);
	i = i + count_nb(data->floor.R);
	i = skip_spa_com(aux, i);
	data->floor.G = ft_atoi(aux + i);
	i = i + count_nb(data->floor.G);
	i = skip_spa_com(aux, i);
	data->floor.B = ft_atoi(aux + i);
	while(ft_isdigit(aux[i]) || aux[i] == ' ' || aux[i] == '\n')
		i++;
	//printf("(%i, %i, %i)\n", data->floor.R, data->floor.G, data->floor.B);
	return (i);
}

int		ft_ceilcol(char *aux, int i, t_data *data)
{
	i = skip_spaces(aux, i);
	data->ceil.R = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.R);
	i = skip_spa_com(aux, i);
	data->ceil.G = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.G);
	i = skip_spa_com(aux, i);
	data->ceil.B = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.B);
	while(aux[i] == '\n')
		i++;
	//printf("(%i, %i, %i)\n", data->ceil.R, data->ceil.G, data->ceil.B);
	return (i);
}

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
	/* Aquí habría que probar qué pasa si las letras del mapa está mal
	¿Reserva el espacio correcto? ¿Puede sar seg fault? */
	data->c = jcpy[1] - j;
	data->map = (char **)malloc(sizeof(char *) * (lines + 1));
	data->map2 = (char **)malloc(sizeof(char *) * (lines + 1));
	data->map[lines] = NULL;
	data->map2[lines] = NULL;
	while (--lines >= 0)
	{
		*(data->map + lines) = (char *)(malloc)(sizeof(char) * (jcpy[1] - j) + 1);
		*(data->map2 + lines) = (char *)(malloc)(sizeof(char) * (jcpy[1] - j) + 1);
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
	alter_map(data);
	check_map_content(data);
	check_map_closed(data);
	/*int		i = 0;
	while (i < l)
	{	
		printf("%s\n", data->map[i]);
		i++;
	}*/
}

void	alter_map(t_data *data) /* Las filas no está NULL-terminated */
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
		data->map[l][c] = '\0';
		l++;
	}
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
	int		i;
	int		j;

	j = 0;
	while (data->map[j]) /* Hay que ver qué hacemos si no encuentra ningún 1 */
	{
		i = 0;
		while (data->map[j][i] && data->map[j][i] != '1')
			i++;
		j++;
	}
	if (j >= data->l || i >= data->c)
	{
		ft_putstr_fd("Error\nInvalid map", 2);
		exit(EXIT_FAILURE);
	}
	else
		map_graph(data);
}

/* j es la línea e i es la columna */

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
				check_one(data, i, j);
		}
	}
	if (!find_ones(data))
	{
		ft_putstr_fd("Error\nInvalid map", 2);
		exit(EXIT_FAILURE);
	}
	/* Después de esto habría que comprobar que el personaje esté dentro del espacio cerrado */
}

/*void	check_map_closed(t_data *data)
{
	int		l;
	int		*n;

	l = 0;
	n = malloc(sizeof(int) * ft_strlen(data->map[0]));
	set_zeros(n, (int)ft_strlen(data->map[0]));
	if (!(try_map(data->map2, l, n)))  Aquí deberíamos salir si el mapa es válido 
	{
		ft_putstr_fd("Error\nMap not closed", 2);
		exit(EXIT_FAILURE);
	}
}*/
/* Esta debería devolver el número de la última línea 
** u otra cosa en caso de que el mapa sea válido */
/*int		try_map(char **map, int l, int *n)
{
	int		*n2;
	int		len;

	len = (int)ft_strlen(map[0]);
	n2 = malloc(sizeof(int) * len);
	while (map[l + 1])
	{
		set_zeros(n, len);
		set_zeros(n2, len);
		set_ones(n, map[l]);
		set_ones(n2, map[l + 1]);
		if (!(compare_lines(n, n2, map, l)))
			return (0);
		l++;
		Tendremos que comprobar aparte la última fila
	}
	return (1);
}*/

/*int		compare_lines(int *n, int *n2, char **map, int l)
{
	int		i;
	int		j;
	int		h;

	i = 0;
	j = (int)ft_strlen(map[0]);
	while (i < j)
	{
		if (n[i] == 1 && n2[i] == 0)
		{
			if ((h = adjacent_ones(n, i, j)) < 2)
			{
				if (adjacent_ones2(map, l, i) == 0)
					return (0);
				if ((adjacent_ones2(map, l, i) == 1) && h == 0)
					return (0);
			}
		}
		i++;
	}
	return (1);
}*/

// Falta ver que la primera línea tenga solo espacios o 1
// Lo mismo con la última línea
// Que los espacios estén rodeados de 1's
// La idea es hacer un mapa alternativo en el que todos los 1's
// que tengan en las 8 casillas que le rodean por lo menos un espacio
// se cambien por ceros. Con esto los unos que están encerrados
// no dan problemas