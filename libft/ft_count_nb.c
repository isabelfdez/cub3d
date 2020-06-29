/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:17:29 by isfernan          #+#    #+#             */
/*   Updated: 2020/03/10 16:18:35 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function counts the digits of a given integer.
** If the integer given is 0, 1 is returned
*/

int		count_nb(int nb)
{
	int				rtrn;
	long long int	i;

	rtrn = 0;
	i = 1;
	while (nb / i)
	{
		i = i * 10;
		rtrn++;
	}
	if (nb <= 0)
		rtrn = rtrn + 1;
	return (rtrn);
}