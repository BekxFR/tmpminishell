/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/15 16:33:29 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_error_doubletab(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		str[i] = NULL;
		i--;
	}
	free(str);
	str = NULL;
}

void	free_error_tripletab(char ***tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}	
	free(tab);
	tab = NULL;
}

void	free_doubletab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_tripletab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab && tab[i])
		i++;
	while (--i >= 0)
	{
		j = 0;
		while (tab[i][j])
			j++;
		while (--j >= 0)
		{
			free(tab[i][j]);
			tab[i][j] = NULL;
		}
		free(tab[i]);
		tab[i] = NULL;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}
