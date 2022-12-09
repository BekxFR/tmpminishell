/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:03 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 13:56:20 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_simple_quote(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] && str[j] == 34 && j < i)
		{	
			j++;
			while (str[j] && str[j] != 34)
				j++;
			if (str[j] != 0 && j > i)
				return (0);
		}
		if (str[j] && str[j] == 39 && j < i)
		{	
			j++;
			while (str[j] && str[j] != 39)
				j++;
			if (str[j] != 0 && j > i)
				return (1);
		}
		j++;
	}
	return (0);
}

int	is_in_quote(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] && str[j] == 34 && j < i)
		{	
			j++;
			while (str[j] && str[j] != 34)
				j++;
			if (str[j] != 0 && j > i)
				return (1);
		}
		if (str[j] && str[j] == 39 && j < i)
		{	
			j++;
			while (str[j] && str[j] != 39)
				j++;
			if (str[j] != 0 && j > i)
				return (1);
		}
		j++;
	}
	return (0);
}
