/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserrano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:31:13 by isfernan          #+#    #+#             */
/*   Updated: 2020/04/24 19:55:47 by aserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = 0;
	n = ft_min(ft_strlen(dst), dstsize);
	j = ft_strlen(src);
	if (dstsize == n)
		return (j + n);
	while (src[i] && i < dstsize - n - 1)
	{
		dst[i + n] = src[i];
		i++;
	}
	dst[i + n] = 0;
	return (j + n);
}
