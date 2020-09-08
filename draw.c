/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/08 20:36:16 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	openwindow(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->resx, data->resy,
		"cub3D");
	data->image.img = mlx_new_image(data->mlx_ptr, data->resx, data->resy);
	data->image.addr = mlx_get_data_addr(data->image.img,
										&data->image.bits_per_pixel,
										&data->image.line_length,
										&data->image.endian);
}

void	draw_screen(t_data *data, t_player *player)
{
	int		x;
	double	**arr;

	x = -1;
	while (++x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initial_dda(player);
		dda(player, data);
		fish_eye(player, data, x);
		verline_tex(x, data, player);
	}
	x = -1;
	arr = calculations_sprite(data, player);
	sort_sprite(data, arr);
	while (++x < data->spr.num)
		transform_sprite(data, player, x, arr);
	x = -1;
	while (++x < data->spr.num)
		free(*(arr + x));
	free(arr);
	if (data->save == 1)
		save_bmp(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image.img, 0, 0);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
