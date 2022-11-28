/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 15:24:32 by mgruson          ###   ########.fr       */
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
}

void free_error_tripletab(char ***tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}	
	free(tab);	
}

void	free_doubletab(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void free_tripletab(char ***tab)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);

}
