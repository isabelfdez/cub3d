/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:39:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/08/17 16:51:20 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TEX_W 64
# define TEX_H 64

# define RIGHT 2
# define LEFT 0
# define TOWARDS 13
# define BACKWARDS 1
# define CAM_RIGHT 124
# define CAM_LEFT 123
# define ESC 53
# define M_SPEED 0.05
# define M_SPEED2 0.05
# define R_SPEED 0.05

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

typedef struct  s_image 
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_image;

typedef	struct	s_texture
{
	char		*N;
	char		*S;
	char		*E;
	char		*W;
}				t_texture;

typedef	struct	s_key
{
	int			right;
	int			left;
	int			towards;
	int			backwards;
	int			arrow_right;
	int			arrow_left;
	int			esc;
}				t_key;

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
	t_dvector	pos;		/* Coordinates of the player */
	t_dvector	dir;		/* Direction that the player is pointing to */
	t_dvector	cam_plane;	/* Amplitude of the player's view */
	double		cameraX;	/* Position of the camera in the camera plane */
	t_dvector	ray_dir;	/* Direction of the ray */
	t_ivector	map;		/* Square of the map where the player is laying */
	t_dvector	side_dist;
	t_dvector	delta_dist;
	t_ivector	step;
	int			hit;		/* 1 is it has hit a wall, 0 otherwise */
	int			side;		/* 0 if the wall hit by the ray is N or S and 1 otherwise */
	double		pwd;
}				t_player;

typedef struct	s_data
{
	int			resx;
	int			resy;
	t_col		floor;
	t_col		ceil;
	char		*floor_col;
	char		*ceil_col;
	char		**map;
	char		**map2;
	int			c;		/* Number of columns in the map */
	int			l;		/* Numer of lines in the map */
	char		dir1;	/* Starting direction of the player */
	void		*mlx_ptr;
	void		*win_ptr;
	t_key		key;
	t_player	*player;
	t_image		image;
	t_texture	texture;
}				t_data;

char	*ft_gnlcub(char **argv);
void	ft_readfile(char *aux);
int		ft_resolution(char *aux, int i, t_data *data);
int		ft_floorcol(char *aux, int i, t_data *data);
int		ft_ceilcol(char *aux, int i, t_data *data);
int		ft_northtex(char *aux, int i, t_data *data);
int		ft_southtex(char *aux, int i, t_data *data);
int		ft_easttex(char *aux, int i, t_data *data);
int		ft_westtex(char *aux, int i, t_data *data);

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
int		*draw_line(t_player *player, t_data *data);

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
void	initialize_keys(t_data *data);
void	print_map(t_data *data);
int		find_key_pressed(t_data *data);
int		nb_sign(int a);
char	*ft_getpath(char *aux, int i, int icpy);
char	*to_base(unsigned int nb);

void	openWindow(t_data *data);
void	draw_screen(t_data *data, t_player *player);
void	verLine(int x, t_data *data, t_player *player);
void	verLine_tex(int x, t_data *data, t_player *player);

int		loop_manager(void *param);
void	key_manager(t_data *data);
int		key_pressed(int key, void *param);
int		key_released(int key, void *param);
int		close_window(void *data);
void	move_towards(t_data *data);
void	move_backwards(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);

#endif