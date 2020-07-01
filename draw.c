/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/01 18:23:06 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	openWindow(t_data *data)
{
    void	*mlx_ptr;
	void	*win_ptr;

    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data->resx, data->resy, "Raycaster");
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
}

void	verLine(int x, int start, int end, t_data *data, t_player *player)
{
	int 	i;

	i = 0;
	while (i < start)
		i++;
	while (i < end)
	{
		if (player->side == 1)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0xFFFF00);
		else
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, i, 0xFFE000);
		i++;
	}
}
