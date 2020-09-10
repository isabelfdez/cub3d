/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archivo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:45:31 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:50:07 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fish_eye(t_player *player, t_data *data, int x)
{
	if (player->side == 0)
		player->pwd = (player->map.x - player->pos.x +
			(1 - player->step.x) / 2) / player->ray_dir.x;
	else
		player->pwd = (player->map.y - player->pos.y +
			(1 - player->step.y) / 2) / player->ray_dir.y;
	data->spr.buff[x] = player->pwd;
}

/*
** line_h is the height of the vertical line that should be drawn
** it is calculated doing the inverse of the perpendicular distance to the wall
** and then multiplying it by the height of pixels of the screen (to bring
** it to pixel coordinates)
*/

int		*draw_line(t_player *player, t_data *data)
{
	int		line_h;
	int		*array;

	array = malloc(sizeof(int) * 2);
	line_h = (int)(data->resy / player->pwd);
	array[0] = -line_h / 2 + data->resy / 2;
	array[1] = line_h / 2 + data->resy / 2;
	if (array[0] < 0)
		array[0] = 0;
	if (array[1] >= data->resy)
		array[1] = data->resy - 1;
	return (array);
}

int		key_pressed(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == ESC)
	{
		data->key.esc++;
		return (0);
	}
	key_right_left(data, key);
	if (key == TOWARDS && data->key.towards == 0)
		data->key.towards++;
	if (key == BACKWARDS && data->key.backwards == 0)
		data->key.backwards++;
	cam_right_left(data, key);
	return (0);
}

void	key_right_left(t_data *data, int key)
{
	if (key == RIGHT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') && data->key.left == 0)
			data->key.left++;
		if ((data->dir1 == 'E' || data->dir1 == 'N') && data->key.right == 0)
			data->key.right++;
	}
	if (key == LEFT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') && data->key.right == 0)
			data->key.right++;
		if ((data->dir1 == 'E' || data->dir1 == 'N') && data->key.left == 0)
			data->key.left++;
	}
}

void	cam_right_left(t_data *data, int key)
{
	if (key == CAM_RIGHT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') &&
			data->key.arrow_left == 0)
			data->key.arrow_left++;
		if ((data->dir1 == 'E' || data->dir1 == 'N') &&
			data->key.arrow_right == 0)
			data->key.arrow_right++;
	}
	if (key == CAM_LEFT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') &&
			data->key.arrow_right == 0)
			data->key.arrow_right++;
		if ((data->dir1 == 'E' || data->dir1 == 'N') &&
			data->key.arrow_left == 0)
			data->key.arrow_left++;
	}
}
