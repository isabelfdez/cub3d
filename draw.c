/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/08/18 18:04:55 by isfernan         ###   ########.fr       */
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
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0, 0);
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
	int		i;
	int		start;
	int		end;
	int		*arr;

    //img.img = mlx_new_image(data->mlx_ptr, data->resx, data->resy);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                             &img.endian);

	//while (x < data->resx)
	//{
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
}

/* Esto no puede estar bien porque estoy teniendo el mismo error que la otra vez;
** recorro los x dos veces, porque uno de los parámetros de la función ya es el x
** en el que me encuentro */

/* Para arreglar esto tengo que mirar en el 42-cub3d. Tiene una función llamada
** get_tex_color. La cosa es que todo lo que yo tengo en la estructura de imagen,
** este señor lo tiene en la de la textura */

/*void	verLine_tex(int x, t_data *data, t_player *player)
{
	int		start;
	int		end;
	int		*arr;
	double	wallX;
	int		texX;
	int		texY;
	int		i;
	double	step;
	int		line_h;
	double	texPos;

	i = 0;
	line_h = (int)(data->resy / player->pwd);
	arr = draw_line(player, data);
	start = arr[0];
	end = arr[1];
	if (player->side == 0)
		wallX = player->pos.y + player->pwd * player->ray_dir.y;
	else
		wallX = player->pos.x + player->pwd * player->ray_dir.x;
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)TEX_W);
	if (player->side == 0 && player->ray_dir.x > 0)
		texX = TEX_W - texX - 1;
	else if (player->side == 1 && player->ray_dir.y < 0)
		texX = TEX_W - texX - 1;
	step = (double)TEX_H / line_h;
	texPos = (start - data->resy / 2 + line_h / 2) * step;
	while (i < start)
	{
		my_mlx_pixel_put(&data->image, x, i, data->ceil_col);
		i++;
	}
	while (i < end)
	{
		texY = (int)texPos;
		texPos += step;
		my_mlx_pixel_put(&data->image, x, i, )
	}
	while (i < data->resy)
	{
		my_mlx_pixel_put(&data->image, x, i, data->floor_col);
		i++;	
	}
	ESTO TENDRÍA QUE IR COMENTADO
	while (i < end)
	{
		if (player->side == 0)
		{
			wallX = player->pos.y + player->pwd * player->ray_dir.y;
			my_mlx_pixel_put(&data->image, x, i, 0xFFFF00);
		}
		else
		{
			wallX = player->pos.x + player->pwd * player->ray_dir.x;
			my_mlx_pixel_put(&data->image, x, i, 0xFFE000);
		}
		i++;
	}
	while (i < data->resy)
	{
		my_mlx_pixel_put(&data->image, x, i, data->floor_col);
		i++;	
	}
}*/

/* 
** Así es como define la estructura de la textura en 42-cub3d

typedef struct	s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	t_pos	start;
	t_pos	end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;
*/
