/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/07 12:56:00 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all(t_m *var)
{
	// (void)var;
	if (var->redir)
		free_tripletab(var->redir);
	if (var->cmd)
		free_tripletab(var->cmd);
	// if (var->env)
	// 	free_doubletab(var->env);
	// if (var->split_path)
	// 	free_doubletab(var->split_path);
	if (var->pid)
		free(var->pid);
	return (1);
}

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

void free_error_tripletab(char ***tab, int i)
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
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
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
			tab[i][j] = NULL;
			j++;
		}
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
