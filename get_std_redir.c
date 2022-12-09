/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_std_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 17:24:35 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out(char *redir_file, char c, t_m *var)
{
	if (var->fdout != 1)
		close(var->fdout);
	if (c == 'S')
	{
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (var->fdout == -1)
			return ;
	}
	if (c == 'D')
	{
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (var->fdout == -1)
			return ;
	}
}

void	in(char *redir_file, char c, t_m *var)
{
	if (var->fdin != 0)
		close(var->fdin);
	if (c == 'S')
	{
		var->fdin = open(redir_file, O_RDONLY, 0777);
		if (var->fdin == -1)
		{
			write(2, "ERROR\n", 6);
			exit (-2);
		}
	}
}

void	ft_fd_init(t_m *var)
{
	if (var->fdin == 0)
	{
		if ((var->exec + 1) != (var->tablen))
			var->fdin = var->pipex[0][0];
	}
	if (var->fdout == 1)
	{
		if ((var->exec + 1) != (var->tablen))
			var->fdout = var->pipex[0][1];
	}
}

void	get_std_redir(char **redir, t_m *var)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<") == 0)
			in(redir[i + 1], 'S', var);
		if (ft_strcmp(redir[i], ">>") == 0)
			out(redir[i + 1], 'D', var);
		if (ft_strcmp(redir[i], ">") == 0)
			out(redir[i + 1], 'S', var);
		i = i + 2;
	}
}
