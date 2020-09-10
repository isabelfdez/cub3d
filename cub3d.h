/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:39:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 18:13:12 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/utils.h"
# include <errno.h>

# define TEX_W 64
# define TEX_H 64
# define TEX_N 0
# define TEX_S 1
# define TEX_E 2
# define TEX_WE 3

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

typedef struct	s_str
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
}				t_str;

typedef	struct	s_int
{
	int		i;
	int		c;
	int		l;
}				t_int;

/*
** cub3d.c
*/

void			ft_readfile(char *aux, int argc, char **argv);
int				get_data(char *aux, t_data *data, int i);

/*
** inputs.c
*/

int				ft_resolution(char *aux, int i, t_data *data);
int				ft_floorcol(char *aux, int i, t_data *data);
int				ft_ceilcol(char *aux, int i, t_data *data);
int				ft_northtex(char *aux, int i, t_data *data);
int				ft_southtex(char *aux, int i, t_data *data);

/*
** inputs2.c
*/

int				ft_easttex(char *aux, int i, t_data *data);
int				ft_westtex(char *aux, int i, t_data *data);
int				ft_sprtex(char *aux, int i, t_data *data);

/*
** create_map.c
*/

void			allocate_map(t_data *data, int j, char *aux);
void			fill_map(t_data *data, int jcpy[], char *aux);
void			alter_map(t_data *data);
void			check_map_content(t_data *data);
void			map_graph(t_data *data);

/*
** check_map.c
*/

void			check_character(t_data *data);
int				check_line_char(t_data *data);
int				check_col_char(t_data *data);

/*
** raycasting.c
*/

void			start_raycasting(t_data *data);
void			set_direction(t_data *data, t_player *player);
void			calculations_ray(t_player *player, int x, int resx);
void			initial_dda(t_player *player);
void			dda(t_player *player, t_data *data);

/*
** press_key.c
*/

void			fish_eye(t_player *player, t_data *data, int x);
int				*draw_line(t_player *player, t_data *data);
int				key_pressed(int key, void *param);
void			key_right_left(t_data *data, int key);
void			cam_right_left(t_data *data, int key);

/*
** release_key.c
*/

int				key_released(int key, void *param);
void			key_r_right_left(t_data *data, int key);
void			cam_r_right_left(t_data *data, int key);

/*
** draw.c
*/

void			openwindow(t_data *data);
void			draw_screen(t_data *data, t_player *player);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);

/*
** screenshot.c
*/

void			save_bmp(t_data *data);
int				write_bmp_header(int fd, int size, t_data *data);
void			set_int_in_char(unsigned char *start, int value);
int				write_bmp_data(int file, t_data *data, int pad);
int				get_color(t_data *data, int x, int y);

/*
** textures.c
*/

void			verline_tex(int x, t_data *data, t_player *player);
void			draw_textures(t_data *data, int *arr, int tex[], double pos[]);
int				get_tex_color(t_data *data, int texx, int texy);
int				texture_number(t_data *data);

/*
** sprite.c
*/

double			**calculations_sprite(t_data *data, t_player *player);
void			sort_sprite(t_data *data, double **arr);
void			transform_sprite(t_data *data, t_player *player, int i,
		double **arr);
void			draw_sprite(t_data *data, int x, int screen);
int				get_tex_color_sprite(t_data *data, int texx, int texy);

/*
** managers.c
*/

int				loop_manager(void *param);
void			key_manager(t_data *data);
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);
int				close_window(void *data);

/*
** movement.c
*/

void			move_towards(t_data *data);
void			move_backwards(t_data *data);
void			move_right(t_data *data);
void			move_left(t_data *data);

#endif
