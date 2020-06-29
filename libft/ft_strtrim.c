/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:56 by isfernan          #+#    #+#             */
/*   Updated: 2019/12/06 21:27:34 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_in(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_trim2(char const *s1, int count, int icpy, int i)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) - count + 1))))
		return (0);
	count = 0;
	while (icpy <= i)
	{
		str[count] = s1[icpy];
		count++;
		icpy++;
	}
	str[count] = 0;
	return (str);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		icpy;
	int		count;
	char	*str;

	i = 0;
	count = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && is_in(s1[i], set))
	{
		count++;
		i++;
	}
	icpy = i;
	if (!s1[i])
		return (ft_strdup(""));
	while (s1[i])
		i++;
	while (is_in(s1[--i], set))
		count++;
	str = ft_trim2(s1, count, icpy, i);
	return (str);
}
