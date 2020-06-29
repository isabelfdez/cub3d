/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:39:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/06/29 16:50:54 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include "mlx.h"
# include "./get_next_line/get_next_line.h"
# include <string.h>
# include <errno.h>


typedef struct	s_col
{
	int		R;
	int		G;
	int		B;
}				t_col;

typedef struct	s_data
{
	int		resx;
	int		resy;
	t_col	floor;
	t_col	ceil;
	char	**map;
	char	**map2;
	int		c;		/* Number of columns in the map */
	int		l;		/* Numer of lines in the map */
}				t_data;

void	ft_readfile(char *aux);
int		ft_resolution(char *aux, int i, t_data *data);
int		ft_floorcol(char *aux, int i, t_data *data);
int		ft_ceilcol(char *aux, int i, t_data *data);

void	allocate_map(t_data *data, int j, char *aux);
void	fill_map(t_data *data, int jcpy[], char *aux);
void	alter_map(t_data *data);
void	check_map_content(t_data *data);
void	check_map_closed(t_data *data);
int		try_map(char **map, int l, int *n);
int		compare_lines(int *n, int *n2, char **map, int l);

void	map_graph(t_data *data);
void	check_character(t_data *data);
int		check_line_char(t_data *data, int l);
int		check_col_char(t_data *data, int c);

int		skip_spaces(char *str, int i);
int		skip_spa_com(char *str, int i);
int		count_from(char c, char *str, int j);
int		map_numbers_spa(char c);
int		map_letters(char c);
int		find_camera(t_data *data, int l);
void	set_zeros(int *n, int l);
void	set_ones(int *n, char *str);
int		adjacent_ones(int *n, int j, int len);
int		adjacent_ones2(char **map, int l, int i);
void	adjacent_spa(t_data *data, int l, int c);
int		deg_vtx(t_data *data, int l, int c);
void	check_one(t_data *data, int l, int c);
int		find_ones(t_data *data);
int		line_character(t_data *data);
int		col_character(t_data *data);

#endif