/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/20 16:26:31 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	openWindow(t_data *data)
{
    data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->resx, data->resy, "Raycaster");
	data->image.img = mlx_new_image(data->mlx_ptr, data->resx, data->resy);
	data->image.addr = mlx_get_data_addr(data->image.img, 
										&data->image.bits_per_pixel, 
										&data->image.line_length,
                                 		&data->image.endian);
	//mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
}

void	draw_screen(t_data *data, t_player *player)
{
	int 	x;

	x = 0;
	while (x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initialDDA(player);
		DDA(player, data);
		fishEye(player);
		verLine(x, data, player);
		x++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
	}
}

/*void	verLine(int x, int start, int end, t_data *data, t_player *player)
{
	int 	i;

	i = 0;
	while (i < start)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0x000000);
		i++;
	}
	while (i < end)
	{
		if (player->side == 1)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0xFFFF00);
		else
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0xFFE000);
		i++;
	}
	while (i < data->resy)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0x000000);
		i++;
	}
}*/

void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	verLine(int x, t_data *data, t_player *player)
{
    /*t_image 	img;
	int			i;

	i = 0;
    img.img = mlx_new_image(data->mlx_ptr, data->resx, data->resy);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	while (i < start)
	{
		my_mlx_pixel_put(&img, x, i, 0x000000);
		i++;
	}
	while (i < end)
	{
		if (player->side == 1)
			my_mlx_pixel_put(&img, x, i, 0xFFFF00);
		else
			my_mlx_pixel_put(&img, x, i, 0xFFE000);
		i++;
	}
	while (i < data->resy)
	{
		my_mlx_pixel_put(&img, x, i, 0x000000);
		i++;
	}
	data->image = &img;*/

    //t_image  img;
	int		i;
	int		start;
	int		end;
	int		*arr;

    //img.img = mlx_new_image(data->mlx_ptr, data->resx, data->resy);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                             &img.endian);

	while (x < data->resx)
	{
		arr = draw_line(player, data);
		start = arr[0];
		end = arr[1];
		i = 0;
		while (i < start)
		{
			my_mlx_pixel_put(&data->image, x, i, 0x000000);
			i++;
		}
		while (i < end)
		{
			if (player->side == 1)
				my_mlx_pixel_put(&data->image, x, i, 0xFFFF00);
			else
				my_mlx_pixel_put(&data->image, x, i, 0xFFE000);
			i++;
		}
		while (i < data->resy)
		{
			my_mlx_pixel_put(&data->image, x, i, 0x000000);
			i++;	
		}
		x++;
	}
	//mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
}
