/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:55:12 by marvin            #+#    #+#             */
/*   Updated: 2020/07/21 20:19:09 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Hay que ver que lines esté bien si añado saltos de línea al final */
/* El ft_atof está comentado porque no reconoce el pow */

// Si me pasan un mapa que no existe, da segmentation fault!

// Hay que hacer que no llegue a pegarse del todo a la pared porque si no se buggea
// (no se mueve porque está atrapado en una pared y detecta que está rodeado por paredes)
// Esto lo he intentado arreglar poniendo lo de 0.2 * nb_sign(player->dir.x) pero está mal

int	main(int argc, char **argv)
{
	char    *file;
	int     fd;
	char	*str;
	char	*aux;
	char	*aux2;

	if (argc < 2)
	{
		ft_putstr_fd("Error\nInvalid arguments", 2);
		exit(EXIT_FAILURE);
	}
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
	ft_readfile(aux);
}

void	ft_readfile(char *aux)
{
	t_data	*data;
	int		j;
	int		i;

	j = 0;
	i = 7;
	if (!(data = malloc(sizeof(t_data))))
		return ; /* Aquí hay que ver qué hacemos */
	while (i > 0) /* Si uno de los parámetros no está, no sale de aquí */
	{
		if (aux[j] == 'R')
			j = ft_resolution(aux, j + 1, data);
		if (aux[j] == 'F')
			j = ft_floorcol(aux, j + 1, data);
		if (aux[j] == 'C')
			j = ft_ceilcol(aux, j + 1, data);
		if (aux[j] == 'N' && aux[j + 1] == 'O')
			j = ft_northtex(aux, j + 2, data);
		if (aux[j] == 'S' && aux[j + 1] == 'O')
			j = ft_southtex(aux, j + 2, data);
		if (aux[j] == 'E' && aux[j + 1] == 'A')
			j = ft_easttex(aux, j + 2, data);
		if (aux[j] == 'W' && aux[j + 1] == 'E')
			j = ft_westtex(aux, j + 2, data);
		i--;
	}
	/* El parámetro j va a ser donde acaben los datos y empiece el mapa */
	allocate_map(data, j, aux);
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
	data->floor_col = ft_strjoin("0x", ft_strjoin(to_base(data->floor.R),
			ft_strjoin(to_base(data->floor.G), to_base(data->floor.B))));
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
	data->ceil_col = ft_strjoin("0x", ft_strjoin(to_base(data->ceil.R),
			ft_strjoin(to_base(data->ceil.G), to_base(data->ceil.B))));
	return (i);
}

int		ft_northtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	data->texture.N = ft_getpath(aux, i, icpy);
	while (aux[icpy] == '\n')
		icpy++;
	return (icpy);
}

int		ft_southtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	data->texture.S = ft_getpath(aux, i, icpy);
	while (aux[icpy] == '\n')
		icpy++;
	return (icpy);
}

int		ft_easttex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	data->texture.E = ft_getpath(aux, i, icpy);
	while (aux[icpy] == '\n')
		icpy++;
	return (icpy);
}

int		ft_westtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	data->texture.W = ft_getpath(aux, i, icpy);
	while (aux[icpy] == '\n')
		icpy++;
	return (icpy);
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
	initialize_keys(data);
	print_map(data);
	ft_putendl_fd(data->map[6], 1);
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
				data->dir1 = data->map[l][c];
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

	x = 0;
	openWindow(data);
	if (!(player = malloc(sizeof(t_player))))
		return ;
	player->pos.x = col_character(data) + 0.5;
	player->pos.y = line_character(data) + 0.5;
	if (data->dir1 == 'N')
		player->dir = create_dvec(0, -1);
	else if (data->dir1 == 'S')
		player->dir = create_dvec(0, 1);
	else if (data->dir1 == 'E')
		player->dir = create_dvec(1, 0);
	else if (data->dir1 == 'W')
		player->dir = create_dvec(-1, 0);
	player->cam_plane = create_dvec(0.66 * fabs(player->dir.y), 0.66 * fabs(player->dir.x)); // No estoy muy segura de esto
	data->map[line_character(data)][col_character(data)] = '0';
	draw_screen(data, player);
	/*while (x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initialDDA(player);
		DDA(player, data);
		fishEye(player);
		draw_line(player, data);
		x++;
	}*/
	data->player = player;
	mlx_hook(data->win_ptr, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_released, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, close_window, data);
	mlx_loop_hook(data->mlx_ptr, loop_manager, data);
	mlx_loop(data->mlx_ptr);
}

void	calculations_ray(t_player *player, int x, int resx)
{
	player->cameraX = 2 * x / (double)resx - 1;
	player->ray_dir.x = player->dir.x + player->cam_plane.x * player->cameraX;
	player->ray_dir.y = player->dir.y + player->cam_plane.y * player->cameraX;
	player->map.x = (int)player->pos.x;
	player->map.y = (int)player->pos.y;
	player->delta_dist.x = sqrt(1 + (pow(player->ray_dir.y, 2) / pow(player->ray_dir.x, 2)));
	player->delta_dist.y = sqrt(1 + (pow(player->ray_dir.x, 2) / pow(player->ray_dir.y, 2)));
	//player->delta_dist.x =  fabs(1 / player->ray_dir.x);
	//player->delta_dist.x = fabs(1 / player->ray_dir.y);
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
	if (player->ray_dir.x < 0)
	{
		player->step.x = -1;
		player->side_dist.x = fabs((player->pos.x - player->map.x) * player->delta_dist.x);
	}
	else
	{
		player->step.x = 1;
		player->side_dist.x = fabs((player->map.x + 1.0 - player->pos.x) * player->delta_dist.x);
	}
	if (player->ray_dir.y < 0)
	{
		player->step.y = -1;
		player->side_dist.y = fabs((player->pos.y - player->map.y) * player->delta_dist.y);
	}
	else
	{
		player->step.y = 1;
		player->side_dist.y = fabs((player->map.y + 1.0 - player->pos.y) * player->delta_dist.y);
	}
}

void	DDA(t_player *player, t_data *data)
{
	while (player->hit == 0)
	{
		//printf("mapx %i mapy %i stepx %i stepy %i\n", player->map.x, player->map.y, player->step.x, player->step.y);
		if (player->side_dist.x <= player->side_dist.y)
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
		//printf("x %d, y %d \n", player->map.x, player->map.y);
		if (data->map[player->map.y][player->map.x] != '0')
			player->hit = 1;
	}
	//printf("hit en x = %i y = %i\n", player->map.x, player->map.y);
}

void	fishEye(t_player *player)
{
	//printf("mapx %i mapy %i stepx %i stepy %i raydirx %f raydiry %f side dist_x %f side dist_y %f\n", player->map.x, player->map.y, 
	//	player->step.x, player->step.y, player->ray_dir.x, player->ray_dir.y, player->side_dist.x, player->side_dist.y);
	if (player->side == 0)
		player->pwd = (player->map.x - player->pos.x + (1 - player->step.x) / 2) / player->ray_dir.x;
	else
		player->pwd = (player->map.y - player->pos.y + (1 - player->step.y) / 2) / player->ray_dir.y;
}

/*void	draw_line(int x, t_player *player, t_data *data)
{
	int		line_h;
	int		start;
	int		end;

	line_h = (int)(data->resy / player->pwd);
	start = -line_h / 2 + data->resy / 2;
	end = line_h / 2 + data->resy / 2;
	//printf("%i, %i\n", start, end);
	if (start < 0)
		start = 0;
	if (end > data->resy)
		end = data->resy - 1;
	verLine(x, start, end, data, player);
	//printf("RAY IS OVER\n");
}*/

int		*draw_line(t_player *player, t_data *data)
{
	int		line_h;
	int		*array;

	array = malloc(sizeof(int) * 2);
	line_h = (int)(data->resy / player->pwd);
	array[0] = -line_h / 2 + data->resy / 2;
	array[1] = line_h / 2 + data->resy / 2;
	if (array[0] < 0)
		array[0] = 0;
	if (array[1] > data->resy)
		array[1] = data->resy - 1;
	return (array);
	//verLine(x, start, end, data, player);
	//printf("RAY IS OVER\n");
}


int		key_pressed(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == ESC)
	{
		data->key.esc++;
		return (0);
	}
	if (key == RIGHT && data->key.right == 0)
		data->key.right++;
	if (key == LEFT && data->key.left == 0)
		data->key.left++;
	if (key == TOWARDS && data->key.towards == 0)
		data->key.towards++;
	if (key == BACKWARDS && data->key.backwards == 0)
		data->key.backwards++;
	if (key == CAM_RIGHT && data->key.arrow_right == 0)
		data->key.arrow_right++;
	if (key == CAM_LEFT && data->key.arrow_left == 0)
		data->key.arrow_left++;
	return (0);
}

int		key_released(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == RIGHT && data->key.right == 1)
		data->key.right--;
	if (key == LEFT && data->key.left == 1)
		data->key.left--;
	if (key == TOWARDS && data->key.towards == 1)
		data->key.towards--;
	if (key == BACKWARDS && data->key.backwards == 1)
		data->key.backwards--;
	if (key == CAM_RIGHT && data->key.arrow_right == 1)
		data->key.arrow_right--;
	if (key == CAM_LEFT && data->key.arrow_left == 1)
		data->key.arrow_left--;
	return (0);
}

int		loop_manager(void *param)
{
	t_data *data;

	data = (t_data *)param;
	key_manager(data);
	return (0);
}

void	key_manager(t_data *data)
{
	if (data->key.esc == 1)
		exit(EXIT_SUCCESS);
	if (data->key.towards == 1)
		move_towards(data);
	if (data->key.backwards == 1)
		move_backwards(data);
	if (data->key.right == 1)
		move_right(data);
	if (data->key.left == 1)
		move_left(data);
	if (data->key.arrow_right == 1)
		rotate_right(data);
	if (data->key.arrow_left == 1)
		rotate_left(data);
	if (find_key_pressed(data))
		draw_screen(data, data->player);
}

void	move_towards(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x + M_SPEED * player->dir.x;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x += M_SPEED * player->dir.x;
	/*if (x < data->c && y < data->l && data->map[x][y] == '0')
	{
		ft_putstr_fd("previous ", 1);
		ft_putnbr_fd((int)(player->pos.x * 1000), 1);
		ft_putchar_fd('\n', 1);
		data->player->pos.x += M_SPEED * player->dir.x;		
		ft_putstr_fd("later ", 1);
		ft_putnbr_fd((int)(player->pos.x * 1000), 1);
		ft_putchar_fd('\n', 1);
		ft_putchar_fd('\n', 1);
	}*/
	x = player->pos.x ;
	y = player->pos.y + M_SPEED * player->dir.y;
	/*if (x < data->c)
	{
		ft_putstr_fd("primera\n", 1);
		if (y < data->l)
		{
			ft_putstr_fd("segunda\n", 1);
			if (data->map[y][x] == '0')
			{
				ft_putstr_fd("tercera\n", 1);
				data->player->pos.y += M_SPEED * player->dir.y;
			}
			else
			{
				printf("el caracter que impide avanzar es: (%i, %i), que es %c\n", y, x, data->map[y][x]);
			}
		}
	}*/
	if (x < data->c && y < data->l && data->map[y][x] == '0')
	{
		//ft_putstr_fd("previous ", 1);
		//ft_putnbr_fd((int)(player->pos.y * 1000), 1);
		//ft_putchar_fd('\n', 1);
		data->player->pos.y += M_SPEED * player->dir.y;
		//ft_putstr_fd("later ", 1);
		//ft_putnbr_fd((int)(player->pos.y * 1000), 1);
		//ft_putchar_fd('\n', 1);
		//ft_putchar_fd('\n', 1);
	}
}

void	move_backwards(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x - M_SPEED2 * player->dir.x;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x -= M_SPEED2 * player->dir.x;
	x = player->pos.x;
	y = player->pos.y - M_SPEED2 * player->dir.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y -= M_SPEED2 * player->dir.y;
}

void	move_right(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x - M_SPEED * player->dir.y;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x -= M_SPEED * player->dir.y;
	x = player->pos.x;
	y = player->pos.y - M_SPEED * player->dir.x;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y += M_SPEED * player->dir.x;
}

void	move_left(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x + M_SPEED * player->dir.y;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x += M_SPEED * player->dir.y;
	x = player->pos.x;
	y = player->pos.y + M_SPEED * player->dir.x;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y -= M_SPEED * player->dir.x;
}

void	rotate_left(t_data *data)
{
	double		dirx;
	double		diry;
	double		planex;
	double		planey;

	dirx = data->player->dir.x;
	diry = data->player->dir.y;
	planex = data->player->cam_plane.x,
	planey = data->player->cam_plane.y;
	data->player->dir.x = cos(-R_SPEED) * dirx - sin(-R_SPEED) * diry;
	data->player->dir.y = sin(-R_SPEED) * dirx + cos(-R_SPEED) * diry;
	data->player->cam_plane.x = cos(-R_SPEED) * planex - sin(-R_SPEED) * planey;
	data->player->cam_plane.y = sin(-R_SPEED) * planex + cos(-R_SPEED) * planey;
}

void	rotate_right(t_data *data)
{
	double		dirx;
	double		diry;
	double		planex;
	double		planey;

	dirx = data->player->dir.x;
	diry = data->player->dir.y;
	planex = data->player->cam_plane.x,
	planey = data->player->cam_plane.y;
	data->player->dir.x = cos(R_SPEED) * dirx - sin(R_SPEED) * diry;
	data->player->dir.y = sin(R_SPEED) * dirx + cos(R_SPEED) * diry;
	data->player->cam_plane.x = cos(R_SPEED) * planex - sin(R_SPEED) * planey;
	data->player->cam_plane.y = sin(R_SPEED) * planex + cos(R_SPEED) * planey;
}

int		close_window(void *data)
{
	(void) *data;
	exit(EXIT_SUCCESS);
	return (0);
}