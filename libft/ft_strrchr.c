/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:17:16 by isfernan          #+#    #+#             */
/*   Updated: 2019/11/18 13:20:17 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	ch;
	char	flag;

	i = 0;
	ch = c;
	flag = 'F';
	while (s[i])
	{
		if (s[i] == ch)
		{
			ptr = (char *)s + i;
			flag = 'T';
		}
		i++;
	}
	if (s[i] == ch)
		return ((char *)s + i);
	if (flag == 'F')
		return (NULL);
	else
		return (ptr);
}
