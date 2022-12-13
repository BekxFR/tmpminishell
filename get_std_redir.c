/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_std_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 12:29:07 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	out(char *redir_file, char c, t_m *var)
{
	var->fd_status_out = 0;
	if (var->fdout != 1)
		close(var->fdout);
	if (c == 'S')
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (c == 'D')
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (var->fdout == -1)
	{
		ft_putstr_fd(redir_file, 2);
		perror(" ");
		var->fd_status_out = 1;
		var->fdout = 1;
		g_exit_status = 1;
		return ;
	}
}

void	in(char *redir_file, char c, t_m *var)
{
	var->fd_status_in = 0;
	if (var->fdin != 0)
		close(var->fdin);
	if (c == 'S')
	{
		var->fdin = open(redir_file, O_RDONLY);
		if (var->fdin == -1)
		{
			ft_putstr_fd(redir_file, 2);
			perror(" ");
			var->fd_status_in = 1;
			var->fdin = 0;
			g_exit_status = 1;
			return ;
		}
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
