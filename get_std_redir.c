/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_std_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/02 18:14:41 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_out(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], ">>") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_redir(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (strcmp(redir[i], "<<") == 0)
			return (1);
		if (strcmp(redir[i], "<") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">>") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	out(char *redir_file, char c, t_m *var)
{
	if (var->fdout)
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
	if (var->fdin)
		close(var->fdin);
	if (c == 'S')
	{
		var->fdin = open(redir_file, O_RDONLY, 0777);
		if (var->fdin == -1)
		{
			write(2, "ERROR\n", 6);
			exit (-2);
		}
		// close(fd);
	}
}

void	ft_fd_init(t_m *var)
{
	if (!var->fdin){
		write(2, "CLOSE FD1\n", 11);
		var->fdin = var->pipex[0];}
	if (!var->fdout){
		write(2, "CLOSE FD2\n", 11);
		var->fdout = var->pipex[1];}
}

void	get_std_redir(char **redir, t_m *var)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (strcmp(redir[i], "<") == 0)
			in(redir[i + 1], 'S', var);
		if (strcmp(redir[i], ">>") == 0)
			out(redir[i + 1], 'D', var);
		if (strcmp(redir[i], ">") == 0)
			out(redir[i + 1], 'S', var);
		i = i + 2;
	}
	ft_fd_init(var);
}
