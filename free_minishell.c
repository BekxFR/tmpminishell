/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 17:29:20 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_child(t_m *var)
{
	free_parent(var);
	free(var->args_line);
	free_doubletab(var->env);
	return (0);
}

int	free_parent(t_m *var)
{
	free_tripletab(var->redir);
	free_tripletab(var->cmd);
	free(var->pid);
	ft_free_inttab(var->pipex);
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
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void free_tripletab(char ***tab)
{
    int i;
    int j;
    
    i = 0;
    if (!tab)
        return ;
    while(tab[i])
        i++;
    while (--i >= 0)
    {
        j = 0;
        while(tab[i][j])
            j++;
        while(--j >= 0)
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
