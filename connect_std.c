/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/05 11:44:24 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir_in(char **redir)
{
	int i;

	i = 0;
	printf("redir[i]=%s\n", redir[i]);
	while(redir[i])
	{
		if (strcmp(redir[i], "<<") == 0)
			return (1);
		if (strcmp(redir[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int is_redir_out(char **redir)
{
	int i;

	i = 0;
	while(redir[i])
	{
		if (ft_strcmp(redir[i], ">>") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">") == 0)
			return (1);
		i++;
	}
	return (0);
}

int out(char *redir_file, char c)
{
	int fd;
		
	if (c == 'D')
	{
	fd = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (-2);
	}
	if (c == 'S')
	{
	fd = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (-2);
	}
	return (fd);
}

int in(char *redir_file, char c, t_m *var)
{
	int fd;

	if (c == 'D')
	{
		// SIGNAL a rajouter et voir comment faire
		write(2, "IN REDIR D\n", 12);
		(*var).comp = ft_strjoin(redir_file, "\n");
		(*var).heredoc_status = 1;
		ft_trunc_init_fd(".tmpheredoc4", &(*var).fdin);
		ft_heredoc_fd(var, 1, 1);
		return (var->fdin);
	}
	if (c == 'S')
	{
		fd = open(redir_file, O_RDONLY, 0777);
		if (fd == -1)
		{	
			// ft_putstr_fd(redir_file, 2);
			// ft_putstr_fd(" : No such file or directory\n", 2);
			write(2, "ERROR\n", 6);
			exit (-2);
		}
	}
	return (fd);
}

int connect_stdin(char **redir, int pipex, t_m *var)
{
	int i;
	int fd;

	fd = pipex;
	i = 0;
	while(redir[i])
	{
		if (strcmp(redir[i], "<<") == 0)
		{
			fd = in(redir[i + 1], 'D', var);
		}
		if (strcmp(redir[i], "<") == 0)
		{
			fd = in(redir[i + 1], 'S', var);
		}
		i = i + 2;
	}
	return (fd);
}

int connect_stdout(char **redir, int pipex)
{
	int i;
	int fd;

	fd = pipex;
	i = 0;
	while(redir[i])
	{
		if (strcmp(redir[i], ">>") == 0)
		{
			fd = out(redir[i + 1], 'D');
		} 
		if (strcmp(redir[i], ">") == 0)
		{
			fd = out(redir[i + 1], 'S');
		}
		i = i + 2;
	}
	return (fd);
}

