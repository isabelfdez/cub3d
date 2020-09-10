/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:26:40 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 16:13:42 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_easttex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	if ((data->texture[TEX_E].path = ft_getpath(aux, i, icpy)))
	{
		while (aux[icpy] == '\n')
			icpy++;
		if ((data->texture[TEX_E].texim.img =
			mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[TEX_E].path, &data->tex_w, &data->tex_h)))
			data->texture[TEX_E].texim.addr =
			mlx_get_data_addr(data->texture[TEX_E].texim.img,
			&data->texture[TEX_E].texim.bits_per_pixel,
			&data->texture[TEX_E].texim.line_length,
			&data->texture[TEX_E].texim.endian);
		else
			exit_program_data(data, 3);
	}
	data->info++;
	return (icpy);
}

int		ft_westtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	if ((data->texture[TEX_WE].path = ft_getpath(aux, i, icpy)))
	{
		while (aux[icpy] == '\n')
			icpy++;
		if ((data->texture[TEX_WE].texim.img =
			mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[TEX_WE].path, &data->tex_w, &data->tex_h)))
			data->texture[TEX_WE].texim.addr =
			mlx_get_data_addr(data->texture[TEX_WE].texim.img,
			&data->texture[TEX_WE].texim.bits_per_pixel,
			&data->texture[TEX_WE].texim.line_length,
			&data->texture[TEX_WE].texim.endian);
		else
			exit_program_data(data, 3);
	}
	data->info++;
	return (icpy);
}

int		ft_sprtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	if ((data->spr.tex.path = ft_getpath(aux, i, icpy)))
	{
		while (aux[icpy] == '\n')
			icpy++;
		if ((data->spr.tex.texim.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->spr.tex.path, &data->tex_w, &data->tex_h)))
			data->spr.tex.texim.addr =
			mlx_get_data_addr(data->spr.tex.texim.img,
			&data->spr.tex.texim.bits_per_pixel,
			&data->spr.tex.texim.line_length, &data->spr.tex.texim.endian);
		else
			exit_program_data(data, 4);
	}
	data->info++;
	return (icpy);
}
