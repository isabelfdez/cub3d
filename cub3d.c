/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:55:12 by marvin            #+#    #+#             */
/*   Updated: 2020/06/30 20:38:17 by isfernan         ###   ########.fr       */
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
	map_graph(data);
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
		data->map2[l][c] = '\0';
		l++;
	}
	data->map2[l] = NULL;
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
				data->dir1 = data->map[l][c];
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
	start_raycasting(data);
}

void	check_character(t_data *data)
{
	int	l;
	int	c;

	l = line_character(data);
	c = col_character(data);
	if (!check_line_char(data, l))
	{
		ft_putstr_fd("Error\nCharacter outside of closed space", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_col_char(data, c))
	{
		ft_putstr_fd("Error\nCharacter outside of closed space", 2);
		exit(EXIT_FAILURE);
	}
}

int		check_line_char(t_data *data, int l)
{
	int c;
	int l2;
	int	j;
	(void)l;

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

int		check_col_char(t_data *data, int c)
{
	int l;
	int c2;
	int j;
	(void)c;

	l = 0;
	while(l < data->l)
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

void	start_raycasting(t_data *data)
{
	t_player	*player;
	int			x;

	write(1, "raycasting\n", 11);
	x = -1;
	if (!(player = malloc(sizeof(t_player))))
		return ;
	player->pos.x = col_character(data);
	player->pos.y = line_character(data);
	if (data->dir1 == 'N')
		player->dir = create_dvec(0, 1);
	else if (data->dir1 == 'S')
		player->dir = create_dvec(0, -1);
	else if (data->dir1 == 'E')
		player->dir = create_dvec(1, 0);
	else if (data->dir1 == 'W')
		player->dir = create_dvec(-1, 0);
	player->cam_plane = create_dvec(0.66 * fabs(player->dir.y), 0.66 * fabs(player->dir.x)); // No estoy muy segura de esto
	while (++x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initialDDA(player);
		DDA(player, data);
		fishEye(player);
		draw_line(x, player, data);
	}
}

void	calculations_ray(t_player *player, int x, int resx)
{
	write(1, "calculations\n", 13);
	player->cameraX = 2 * x / (double)resx - 1;
	player->ray_pos.x = player->pos.x;
	player->ray_pos.y = player->pos.y;
	player->ray_dir.x = player->dir.x + player->cam_plane.x * player->cameraX;
	player->ray_dir.y = player->dir.y + player->cam_plane.y * player->cameraX;
	player->map.x = (int)player->pos.x;
	player->map.y = (int)player->pos.y;
	player->delta_dist.x =  1 / player->ray_dir.x;
	player->delta_dist.x = 1 / player->ray_dir.y;
	//player->delta_dist.x = (player->ray_dir.y == 0) ? 0 : ((player->ray_dir.x == 0) ? 1 : fabs(1 / player->ray_dir.x));
    //player->delta_dist.y = (player->ray_dir.x == 0) ? 0 : ((player->ray_dir.y == 0) ? 1 : fabs(1 / player->ray_dir.y));
	player->hit = 0;
	player->side = 0;
	player->step = create_ivec(0, 0);
}

/* 
** The DDA algorithm will always jump exactly one square each loop, either a 
** square in the x-direction, or a square in the y-direction. If it has to go 
** in the negative or positive x-direction, and the negative or positive 
** y-direction will depend on the direction of the ray, and this fact will be 
** stored in step.x and step.y. Those variables are always either -1 or +1.
*/

void	initialDDA(t_player *player)
{
	write(1, "iDDA\n", 5);
	if (player->ray_dir.x < 0)
	{
		player->step.x = -1;
		player->side_dist.x = (player->ray_pos.x - player->map.x) * player->delta_dist.x;
	}
	else
	{
		player->step.x = 1;
		player->side_dist.x = (player->map.x + 1 - player->ray_pos.x) * player->delta_dist.x;
	}
	if (player->ray_dir.y < 0)
	{
		player->step.y = -1;
		player->side_dist.y = (player->ray_pos.y - player->map.y) * player->delta_dist.y;
	}
	else
	{
		player->step.y = 1;
		player->side_dist.y = (player->map.y + 1 - player->ray_pos.y) * player->delta_dist.y;
	}
}

void	DDA(t_player *player, t_data *data)
{
	write(1, "DDA\n", 4);
	while (player->hit == 0)
	{
		if (player->side_dist.x > player->side_dist.y)
		{
			player->side_dist.x += player->delta_dist.x;
			player->map.x += player->step.x;
			player->side = 0;
		}
		else
		{
			player->side_dist.y += player->delta_dist.y;
			player->map.y += player->step.y;
			player->side = 1;
		}
		printf("x %d, y %d \n", player->map.x, player->map.y);
		//if (data->map[player->map.x][player->map.y] != 0)
			//player->hit = 1;
	}
}

void	fishEye(t_player *player)
{
	write(1, "fE\n", 3);
	if (player->side == 0)
		player->pwd = (player->map.x - player->ray_pos.x + (1 - player->step.x) / 2) / player->ray_dir.x;
	else
		player->pwd = (player->map.y - player->ray_pos.y + (1 - player->step.y) / 2) / player->ray_dir.y;
}

void	draw_line(int x, t_player *player, t_data *data)
{
	write(1, "draw\n", 5);
	int		line_h;
	int		start;
	int		end;

	line_h = data->resy / (int)player->pwd;
	start = -line_h / 2 + data->resy / 2;
	end = line_h / 2 + data->resy / 2;
	if (start < 0)
		start = 0;
	if (end > data->resy)
		end = data->resy - 1;
	//verLine(x, start, end, data);
}
