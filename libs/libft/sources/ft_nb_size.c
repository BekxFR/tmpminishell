/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:40:46 by chillion          #+#    #+#             */
/*   Updated: 2022/09/02 17:43:35 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_size(int nb, char *base)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(base);
	if (len == 0)
	{
		return (i);
	}
	if (nb <= 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb != 0)
	{
		nb = nb / len;
		i++;
	}
	return (i);
}
