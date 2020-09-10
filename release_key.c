/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:49:50 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:50:04 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_released(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	key_r_right_left(data, key);
	if (key == TOWARDS && data->key.towards == 1)
		data->key.towards--;
	if (key == BACKWARDS && data->key.backwards == 1)
		data->key.backwards--;
	cam_r_right_left(data, key);
	return (0);
}

void	key_r_right_left(t_data *data, int key)
{
	if (key == RIGHT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') && data->key.left == 1)
			data->key.left--;
		if ((data->dir1 == 'E' || data->dir1 == 'N') && data->key.right == 1)
			data->key.right--;
	}
	if (key == LEFT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') && data->key.right == 1)
			data->key.right--;
		if ((data->dir1 == 'E' || data->dir1 == 'N') && data->key.left == 1)
			data->key.left--;
	}
}

void	cam_r_right_left(t_data *data, int key)
{
	if (key == CAM_RIGHT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') &&
			data->key.arrow_left == 1)
			data->key.arrow_left--;
		if ((data->dir1 == 'E' || data->dir1 == 'N') &&
			data->key.arrow_right == 1)
			data->key.arrow_right--;
	}
	if (key == CAM_LEFT)
	{
		if ((data->dir1 == 'W' || data->dir1 == 'S') &&
			data->key.arrow_right == 1)
			data->key.arrow_right--;
		if ((data->dir1 == 'E' || data->dir1 == 'N') &&
			data->key.arrow_left == 1)
			data->key.arrow_left--;
	}
}
