/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 17:54:06 by isfernan         ###   ########.fr       */
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

	x = -1;
	while (++x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initialDDA(player);
		DDA(player, data);
		fishEye(player, data, x);
		verline_tex(x, data, player);
	}
	x = -1;
	calculations_sprite(data, player);
	sort_sprite(data);
	while (++x < data->spr.num)
		transform_sprite(data, player, x);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->image.img, 0, 0);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
