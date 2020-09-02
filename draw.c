/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/02 20:35:23 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	openWindow(t_data *data)
{
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

	x = -1;
	while (++x < data->resx)
	{
		calculations_ray(player, x, data->resx);
		initialDDA(player);
		DDA(player, data);
		fishEye(player, data, x);
		verLine_tex(x, data, player);
	}
	x = -1;
	calculations_sprite(data, player);
	sort_sprite(data);
	while (++x < data->spr.num)
		transform_sprite(data, player, x);
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
			my_mlx_pixel_put(&data->image, x, i, data->ceil_col);
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
			my_mlx_pixel_put(&data->image, x, i, data->floor_col);
			i++;	
		}
}

void	verLine_tex(int x, t_data *data, t_player *player)
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
		my_mlx_pixel_put(&data->image, x, i, 0x000000);
		i++;
	}
	while (i < end)
	{
		texY = (int)texPos;
		texPos += step;
		my_mlx_pixel_put(&data->image, x, i, get_tex_color(data, texX, texY));
		i++;
	}
	while (i < data->resy)
	{
		my_mlx_pixel_put(&data->image, x, i, 0x000000);
		i++;	
	}
}

int		get_tex_color(t_data *data, int texX, int texY)
{
	if (texX >= 0 && texX < data->tex_w
		&& texY >= 0 && texY < data->tex_h)
		{
			return (*(int *)(data->texture[texture_number(data)].texim.addr
				+ (4 * data->tex_w * texY)
				+ (4 * texX)));
		}
	return (0x0);
}

int		get_tex_color_sprite(t_data *data, int texX, int texY)
{
	if (texX >= 0 && texX < data->tex_w
		&& texY >= 0 && texY < data->tex_h)
		{
			return (*(int *)(data->spr.tex.texim.addr
				+ (4 * data->tex_w * texY)
				+ (4 * texX)));
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

void	calculations_sprite(t_data *data, t_player *player)
{
	int		i;
	int		c;
	int		l;

	i = -1;
	l = 0;
	data->spr.arr = malloc(sizeof(double *) * data->spr.num);
	while (++i < data->spr.num)
		data->spr.arr[i] = malloc((sizeof(double)) * 4);
	i = 0;
	while (l < data->l && i < data->spr.num)
	{
		c = 0;
		while (c < data->c && i < data->spr.num)
		{
			if (data->map[l][c] == '2')
			{
				data->spr.arr[i][0] = i;
				data->spr.arr[i][1] = (double)c + 0.5;
				data->spr.arr[i][2] = (double)l + 0.5;
				data->spr.arr[i][3] = pow(player->pos.x - data->spr.arr[i][1], 2)
					+ pow(player->pos.y - data->spr.arr[i][2], 2);
				i++;
			}
			c++;
		}
		l++;
	}
}

void	sort_sprite(t_data *data)
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
			if (data->spr.arr[i][3] < data->spr.arr[i + 1][3])
			{
				aux = data->spr.arr[i];
				data->spr.arr[i] = data->spr.arr[i + 1];
				data->spr.arr[i + 1] = aux;
			}
			i++;
		}
		flag = check_order(data);
	}
}

/*
** To calculate the sprite height and width I use the same formula
** as when I had to calculate the line height in draw_line().
** However, this time I use transY (which is actually the depth inside 
** the screen) because it prevents fisheye
*/

void	transform_sprite(t_data *data, t_player *player, int i)
{
	double	det_inv;
	int		screen;
	int		x;

	det_inv = 1.0 / (player->cam_plane.x * player->dir.y -
		player->cam_plane.y * player->dir.x);
	data->spr.sprX = data->spr.arr[i][1] - player->pos.x;
	data->spr.sprY = data->spr.arr[i][2] - player->pos.y;
	data->spr.transX = det_inv * (player->dir.y * data->spr.sprX
		- player->dir.x * data->spr.sprY);
	data->spr.transY = det_inv * (player->cam_plane.x * data->spr.sprY
		- player->cam_plane.y * data->spr.sprX);
	screen = (int)((data->resx / 2) * (1 + data->spr.transX /
		data->spr.transY));
	data->spr.h = abs((int)(data->resy / data->spr.transY));
	if ((data->spr.startY = data->resy / 2 - data->spr.h / 2) < 0)
		data->spr.startY = 0;
	if ((data->spr.endY = data->resy / 2 + data->spr.h / 2) >= data->resy)
		data->spr.endY = data->resy - 1;
	data->spr.w = abs((int)(data->resy / data->spr.transY));
	if ((data->spr.startX = screen - data->spr.w / 2) < 0)
		data->spr.startX = 0;
	if ((data->spr.endX = screen + data->spr.w / 2) >= data->resx)
		data->spr.endY = data->resx - 1;
	x = data->spr.startX - 1;
	while (++x < data->spr.endX)
		draw_sprite(data, x, screen);
}

void	draw_sprite(t_data *data, int x, int screen)
{
	int		y;
	int		texX;
	int		texY;
	int		d;
	int		color;

	y = data->spr.startY - 1;
	texX = (int)((x - (screen - data->spr.w / 2)) * TEX_W / data->spr.w);
	if (data->spr.transY > 0 && x > 0 && x < data->resx && data->spr.transY < data->spr.buff[x])
	{
		while (++y < data->spr.endY)
		{
			d = y * 256 - data->resy * 128 + data->spr.h * 128;
			texY = ((d * TEX_H) / data->spr.h) / 256;
			color = get_tex_color_sprite(data, texX, texY);
			if (color != 0x000000)
				my_mlx_pixel_put(&data->image, x, y, color);
		}
	}
}
