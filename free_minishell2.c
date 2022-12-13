/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:10:54 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 10:49:01 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_child_heredoc(t_m *var)
{
	free_tripletab(var->redir);
	free_tripletab(var->cmd);
	free(var->pid);
	free(var->args_line);
	free_doubletab(var->env);
	return (0);
}

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

void	ft_free_inttab(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
