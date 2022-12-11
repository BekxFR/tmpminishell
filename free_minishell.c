/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 18:41:13 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all(t_m *var)
{
	if (var->redir)
		free_tripletab(var->redir);
	if (var->cmd)
		free_tripletab(var->cmd);
	// ft_free_inttab(var->pipex);
	if (var->pid)
		free(var->pid);
	// if (var->env)
	// 	free_doubletab(var->env);
	// if (var->split_path)
	// 	free_doubletab(var->split_path);
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

// void free_tripletab(char ***tab)
// {
// 	int i;
// 	int j;
	
// 	i = 0;
// 	j = 0;
// 	if (!tab)
// 		return ;
// 	while (tab[i])
// 	{
// 		j = 0;
// 		while(tab[i][j])
// 		{
// 			free(tab[i][j]);
// 			tab[i][j] = NULL;
// 			j++;
// 		}
// 		free(tab[i]);
// 		tab[i] = NULL;
// 		i++;
// 	}
// 	if (*tab)
// 	{
// 		free(tab);
// 		tab = NULL;
// 	}
// }

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


void free_tripletab2(t_m *var)
{
	int i;
	int j;
	
	i = 0;
	if (!var->cmd)
		return ;
	while(var->cmd[i])
		i++;
	while (--i >= 0)
	{
		j = 0;
		while(var->cmd[i][j])
			j++;
		while(--j >= 0)
		{
			free(var->cmd[i][j]);
			var->cmd[i][j] = NULL;
		}
		free(var->cmd[i]);
	}
	if (var->redir)
	{
		free(var->redir);
		var->redir = NULL;
	}
	if (var->cmd)
	{
		free(var->cmd);
		var->cmd = NULL;
	}
	// free(var->cmd);
	// free(var->redir);
	// if (var->cmd)
	// {
	// 	free(var->cmd);
	// 	var->cmd = NULL;
	// }
/*
	while (var->cmd[i])
	{
		j = 0;
		while(var->cmd[i][j])
		{
			// free(var->cmd[i][j]);
			// var->cmd[i][j] = NULL;
			j++;
		}
		printf("J=%d, i=%d\n", j , i);
		// free(var->cmd[i]);
		// var->cmd[i] = NULL;
		i++;
	}
	printf("J=%d, i=%d\n", j , i);
	// free(var->cmd[0][2]);
	// free(var->cmd[2][0]);
	free(var->cmd[1]);
	free(var->cmd[0][1]);
	free(var->cmd[0][0]);
	free(var->cmd[0]);
	// free(var->cmd[0][2]);
	free(var->cmd);
	free(var->redir);
	// if (*var->cmd)
	// {
	// 	free(var->cmd);
	// 	var->cmd = NULL;
	// }
*/
}