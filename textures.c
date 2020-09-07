/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 17:38:00 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/07 20:24:48 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** tex[0] = texX, tex[1] = texY, tex[2] = x, pos[0] = texPos, pos[1] = step
*/

void	verline_tex(int x, t_data *data, t_player *player)
{
	int		*arr;
	double	wallx;
	int		tex[3];
	int		line_h;
	double	pos[2];

	tex[2] = x;
	line_h = (int)(data->resy / player->pwd);
	arr = draw_line(player, data);
	if (player->side == 0)
		wallx = player->pos.y + player->pwd * player->ray_dir.y;
	else
		wallx = player->pos.x + player->pwd * player->ray_dir.x;
	wallx -= floor(wallx);
	tex[0] = (int)(wallx * (double)TEX_W);
	if (player->side == 0 && player->ray_dir.x > 0)
		tex[0] = TEX_W - tex[0] - 1;
	else if (player->side == 1 && player->ray_dir.y < 0)
		tex[0] = TEX_W - tex[0] - 1;
	pos[1] = (double)TEX_H / line_h;
	pos[0] = (arr[0] - data->resy / 2 + line_h / 2) * pos[1];
	draw_textures(data, arr, tex, pos);
	free(arr);
}

void	draw_textures(t_data *data, int *arr, int tex[], double pos[])
{
	int		i;
	int		x;

	x = tex[2];
	i = -1;
	while (++i < arr[0])
		my_mlx_pixel_put(&data->image, x, i, data->c_c);
	while (++i < arr[1])
	{
		tex[1] = (int)pos[0];
		pos[0] += pos[1];
		my_mlx_pixel_put(&data->image, x, i, get_tex_color(data, tex[0],
			tex[1]));
	}
	while (++i < data->resy)
		my_mlx_pixel_put(&data->image, x, i, data->f_c);
}

int		get_tex_color(t_data *data, int texx, int texy)
{
	if (texx >= 0 && texx < data->tex_w
		&& texy >= 0 && texy < data->tex_h)
	{
		return (*(int *)(data->texture[texture_number(data)].texim.addr
			+ (4 * data->tex_w * texy)
			+ (4 * texx)));
	}
	return (0x0);
}

int		texture_number(t_data *data)
{
	if (data->player->side == 0 && data->player->ray_dir.x > 0)
		return (TEX_E);
	if (data->player->side == 0 && data->player->ray_dir.x < 0)
		return (TEX_WE);
	if (data->player->side == 1 && data->player->ray_dir.y > 0)
		return (TEX_S);
	if (data->player->side == 1 && data->player->ray_dir.y < 0)
		return (TEX_N);
	return (0);
}
