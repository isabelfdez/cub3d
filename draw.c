/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:52:28 by isfernan          #+#    #+#             */
/*   Updated: 2020/06/30 20:06:21 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verLine(int x, int start, int end, t_data *data)
{
    void	*mlx_ptr;
	void	*win_ptr;
	int		i;

	i = -1;
    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data->resx, data->resy, "Raycaster");
	while (i < start)
		i++;
	while (i < end)
		mlx_pixel_put(mlx_ptr, win_ptr, i, x, 0xFFFF00);
	mlx_loop(mlx_ptr);
}