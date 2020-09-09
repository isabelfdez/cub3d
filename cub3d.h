/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:39:56 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/09 19:57:59 by isfernan         ###   ########.fr       */
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

char	*ft_gnlcub(char **argv);
void	ft_readfile(char *aux, int argc, char **argv);
int		get_data(char *aux, t_data *data, int i);

int		ft_resolution(char *aux, int i, t_data *data);
int		ft_floorcol(char *aux, int i, t_data *data);
int		ft_ceilcol(char *aux, int i, t_data *data);
int		ft_northtex(char *aux, int i, t_data *data);
int		ft_southtex(char *aux, int i, t_data *data);
int		ft_easttex(char *aux, int i, t_data *data);
int		ft_westtex(char *aux, int i, t_data *data);
int		ft_sprtex(char *aux, int i, t_data *data);

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
void	initial_dda(t_player *player);
void	dda(t_player *player, t_data *data);
void	fish_eye(t_player *player, t_data *data, int x);
int		*draw_line(t_player *player, t_data *data);

void	openwindow(t_data *data);
void	draw_screen(t_data *data, t_player *player);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

int		get_color(t_data *data, int x, int y);
int		write_bmp_data(int file, t_data *data, int pad);
void	set_int_in_char(unsigned char *start, int value);
int		write_bmp_header(int fd, int size, t_data *data);
void	save_bmp(t_data *data);

void	verline_tex(int x, t_data *data, t_player *player);
int		get_tex_color(t_data *data, int texx, int texy);
int		texture_number(t_data *data);
void	draw_textures(t_data *data, int *arr, int tex[], double pos[]);

double	**calculations_sprite(t_data *data, t_player *player);
void	sort_sprite(t_data *data, double **arr);
void	transform_sprite(t_data *data, t_player *player, int i, double **arr);
void	draw_sprite(t_data *data, int x, int screen);
int		get_tex_color_sprite(t_data *data, int texx, int texy);

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
