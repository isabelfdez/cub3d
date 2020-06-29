/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserrano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:53:11 by aserrano          #+#    #+#             */
/*   Updated: 2020/03/12 17:38:48 by aserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function counts how many times does the string 
** tofind appear in the string haystack
*/

int		ft_strcnt(char *tofind, char *haystack)
{
	int		counter;
	char	*ptr;
	char	*aux;

	aux = haystack;
	counter = 0;
	while ((ptr = ft_strnstr3(aux, tofind, ft_strlen(haystack))))
	{
		counter++;
		aux = ptr + ft_strlen(tofind);
	}
	return (counter);
}