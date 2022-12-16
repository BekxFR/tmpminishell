/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_are_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:23 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 11:59:05 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	quote_are_closed(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 33)
		{
			i++;
			while (str[i] && str[i] != 33)
				i++;
			if (str[i] == 0)
				return (rite(1, "Error : close the double quote\n", 31), 0);
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] == 0)
				return (write(1, "Error : close the simple quote\n", 31), 0);
		}
		i++;
	}
	return (1);
}
