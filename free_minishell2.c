/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:10:54 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/16 19:27:03 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_child_heredoc(t_m *var)
{
	if (var->redir)
		free_tripletab(var->redir);
	if (var->cmd)
		free_tripletab(var->cmd);
	if (var->pid)
		free(var->pid);
	if (var->args_line)
		free(var->args_line);
	if (var->env)
		free_doubletab(var->env);
	return (0);
}

int	free_child(t_m *var)
{
	free_parent(var);
	if (var->args_line)
		free(var->args_line);
	if (var->env)
		free_doubletab(var->env);
	return (0);
}

int	free_parent(t_m *var)
{
	if (var->redir)
		free_tripletab(var->redir);
	if (var->cmd)
		free_tripletab(var->cmd);
	if (var->pid)
		free(var->pid);
	if (var->pipex)
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
	if (tab)
		free(tab);
}
