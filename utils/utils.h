/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:18:08 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/04 19:57:59 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mlx.h"
# include "../get_next_line/get_next_line.h"

# define TEXTURES 4

typedef struct	s_col
{
	int			r;
	int			g;
	int			b;
}				t_col;

typedef struct	s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef	struct	s_tex
{
	char		*path;
	t_image		texim;
}				t_tex;

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

/*
** num = number of sprites in the map
** tex = texture of the sprite
** arr = for each sprite: order, posx, posy, distance
** sprx = sprite position relative to camera
** trnx = transform sprite with the inverse camera matrix
** trny = depth inside the screen
** h = height of the sprite on the screen
** w = width of the sprite on the screen
** start_x = x-coordinate of the pixel where the sprite starts
** end_x = x-coordinate of the pixel where the sprite ends
** start_y = lowest (up) pixel to fill in current sripe
** end_y = highest (down) pixel to fill in current stripe
*/

typedef	struct	s_sprite
{
	int			num;
	t_tex		tex;
	double		**arr;
	double		sprx;
	double		spry;
	double		trnx;
	double		trny;
	int			h;
	int			w;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	double		*buff;
}				t_sprite;

/*
** pos = coordinates of the player
** dir = direction where the player is pointing to
** cam_plane = amplitude of the player's view
** camerax = position of the camera in the camera plane
** ray_dir = direction of the ray
** map = square of the map where the player lays
** hit = 1 if ray has hit a wall, 0 otherwise
** side = 0 if the wall hit by the ray is N or S and 1 otherwise
** pwd = perpendicular wall distance
*/

typedef	struct	s_player
{
	t_dvector	pos;
	t_dvector	dir;
	t_dvector	cam_plane;
	double		camerax;
	t_dvector	ray_dir;
	t_ivector	map;
	t_dvector	side_dist;
	t_dvector	delta_dist;
	t_ivector	step;
	int			hit;
	int			side;
	double		pwd;
}				t_player;

/*
** c = number of columns in the map
** l = numer of lines in the map
** dir1 = starting direction of the player
*/

typedef struct	s_data
{
	int			resx;
	int			resy;
	t_col		floor;
	t_col		ceil;
	char		*floor_col;
	int			f_c;
	char		*ceil_col;
	int			c_c;
	char		**map;
	char		**map2;
	int			c;
	int			l;
	char		dir1;
	void		*mlx_ptr;
	void		*win_ptr;
	t_key		key;
	t_player	*player;
	t_image		image;
	t_tex		texture[TEXTURES];
	t_sprite	spr;
	int			tex_w;
	int			tex_h;
	int			info;
}				t_data;

int				skip_spaces(char *str, int i);
int				skip_spa_com(char *str, int i);
int				count_from(char c, char *str, int j);
int				map_numbers_spa(char c);
int				map_letters(char c);
int				find_camera(t_data *data, int l);
void			set_zeros(int *n, int l);
void			set_ones(int *n, char *str);
int				adjacent_ones(int *n, int j, int len);
int				adjacent_ones2(char **map, int l, int i);
int				deg_vtx(t_data *data, int l, int c);
void			check_one(t_data *data, int l, int c);
int				find_ones(t_data *data);
int				line_character(t_data *data);
int				col_character(t_data *data);
t_dvector		create_dvec(double i, double j);
t_ivector		create_ivec(int i, int j);
void			initialize_keys(t_data *data);
int				find_key_pressed(t_data *data);
int				nb_sign(int a);
char			*ft_getpath(char *aux, int i, int icpy);
char			*to_base(unsigned int nb);
void			count_sprites(t_data *data);
int				check_colors(t_data *data);
void			exit_program_data(t_data *data, int i);
char			check_order(t_data *data);
int				number_base(char *str);
double			invdet(t_player *player);

#endif
