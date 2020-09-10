/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:38:41 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 18:00:44 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	**calculations_sprite(t_data *data, t_player *pyr)
{
	t_int	k;
	double	**arr;

	k.i = -1;
	k.l = 0;
	arr = (double **)malloc(sizeof(double *) * data->spr.num);
	while (++k.i < data->spr.num)
		arr[k.i] = (double *)malloc((sizeof(double)) * 4);
	k.i = 0;
	while (++k.l < data->l && k.i < data->spr.num)
	{
		k.c = 0;
		while (++k.c < data->c && k.i < data->spr.num)
			if (data->map[k.l][k.c] == '2')
			{
				arr[k.i][0] = k.i;
				arr[k.i][1] = (double)k.c + 0.5;
				arr[k.i][2] = (double)k.l + 0.5;
				arr[k.i][3] = pow(pyr->pos.x - arr[k.i][1], 2)
					+ pow(pyr->pos.y - arr[k.i][2], 2);
				k.i++;
			}
	}
	return (arr);
}

void	sort_sprite(t_data *data, double **arr)
{
	char	flag;
	int		i;
	double	*aux;

	flag = 'F';
	i = 0;
	while (flag == 'F')
	{
		i = 0;
		while (i < data->spr.num - 1)
		{
			if (arr[i][3] < arr[i + 1][3])
			{
				aux = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = aux;
			}
			i++;
		}
		flag = check_order(data, arr);
	}
}

/*
** To calculate the sprite height and width I use the same formula
** as when I had to calculate the line height in draw_line().
** However, this time I use transY (which is actually the depth inside
** the screen) because it prevents fisheye
*/

void	transform_sprite(t_data *data, t_player *player, int i, double **arr)
{
	double	det_inv;
	int		screen;
	int		x;

	det_inv = invdet(player);
	data->spr.sprx = arr[i][1] - player->pos.x;
	data->spr.spry = arr[i][2] - player->pos.y;
	data->spr.trnx = det_inv * (player->dir.y * data->spr.sprx
		- player->dir.x * data->spr.spry);
	data->spr.trny = det_inv * (player->cam_plane.x * data->spr.spry
		- player->cam_plane.y * data->spr.sprx);
	screen = (int)((data->resx / 2) * (1 + data->spr.trnx / data->spr.trny));
	data->spr.h = abs((int)(data->resy / data->spr.trny));
	if ((data->spr.start_y = data->resy / 2 - data->spr.h / 2) < 0)
		data->spr.start_y = 0;
	if ((data->spr.end_y = data->resy / 2 + data->spr.h / 2) >= data->resy)
		data->spr.end_y = data->resy - 1;
	data->spr.w = abs((int)(data->resy / data->spr.trny));
	if ((data->spr.start_x = screen - data->spr.w / 2) < 0)
		data->spr.start_x = 0;
	if ((data->spr.end_x = screen + data->spr.w / 2) >= data->resx)
		data->spr.end_y = data->resx - 1;
	x = data->spr.start_x - 1;
	while (++x < data->spr.end_x)
		draw_sprite(data, x, screen);
}

void	draw_sprite(t_data *data, int x, int screen)
{
	int		y;
	int		texx;
	int		texy;
	int		d;
	int		color;

	y = data->spr.start_y - 1;
	texx = (int)((x - (screen - data->spr.w / 2)) * TEX_W / data->spr.w);
	if (data->spr.trny > 0 && x > 0 && x < data->resx && data->spr.trny
		< data->spr.buff[x])
	{
		while (++y < data->spr.end_y)
		{
			d = y * 256 - data->resy * 128 + data->spr.h * 128;
			texy = ((d * TEX_H) / data->spr.h) / 256;
			color = get_tex_color_sprite(data, texx, texy);
			if (color != 0x000000)
				my_mlx_pixel_put(&data->image, x, y, color);
		}
	}
}

int		get_tex_color_sprite(t_data *data, int texx, int texy)
{
	if (texx >= 0 && texx < data->tex_w
		&& texy >= 0 && texy < data->tex_h)
	{
		return (*(int *)(data->spr.tex.texim.addr
			+ (4 * data->tex_w * texy)
			+ (4 * texx)));
	}
	return (0x0);
}
