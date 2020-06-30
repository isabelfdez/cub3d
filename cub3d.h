/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:39:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/06/30 20:06:59 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "./get_next_line/get_next_line.h"
# include <string.h>
# include <errno.h>


typedef struct	s_col
{
	int			R;
	int			G;
	int			B;
}				t_col;

typedef struct	s_data
{
	int			resx;
	int			resy;
	t_col		floor;
	t_col		ceil;
	char		**map;
	char		**map2;
	int			c;		/* Number of columns in the map */
	int			l;		/* Numer of lines in the map */
	char		dir1;	/* Starting direction of the player */
}				t_data;

typedef	struct	s_dvector
{
	double		x;
	double		y;
}				t_dvector;

typedef	struct	s_ivector
{
	int			x;
	int			y;
}				t_ivector;

typedef	struct	s_player
{
	t_dvector	pos;		/* Coordinates of the playes */
	t_dvector	dir;		/* Direction that the player is pointing to */
	t_dvector	cam_plane;	/* Amplitude of the player's view */
	double		cameraX;	/* Position of the camera in the camera plane */
	t_dvector	ray_pos;	/* Coordinates of the emerging point of the ray */
	t_dvector	ray_dir;	/* Direction of the ray */
	t_ivector	map;		/* Square of the map where the player is laying */
	t_dvector	side_dist;
	t_dvector	delta_dist;
	t_ivector	step;
	int			hit;		/* 1 is it has hit a wall, 0 otherwise */
	int			side;		/* 0 if the wall hit by the reay is N or S and 1 otherwise */
	double		pwd;
}				t_player;


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

void	start_raycasting(t_data *data);
void	calculations_ray(t_player *player, int x, int resx);
void	initialDDA(t_player *player);
void	DDA(t_player *player, t_data *data);
void	fishEye(t_player *player);
void	draw_line(int x, t_player *player, t_data *data);

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
t_dvector	create_dvec(double i, double j);
t_ivector	create_ivec(int i, int j);


void	verLine(int x, int start, int end, t_data *data);

#endif