/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:31:02 by chillion          #+#    #+#             */
/*   Updated: 2022/12/13 11:32:13 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_init_fd_redir(t_m *var)
{
	var->fd_status_in = 0;
	var->fd_status_out = 0;
	if (var->exec == 0)
		var->fdin = 0;
	else
		var->fdin = var->pipex[var->exec - 1][0];
	if ((var->exec + 1) == (var->tablen))
	{
		close(var->pipex[var->exec][0]);
		close(var->pipex[var->exec][1]);
		var->fdout = 1;
	}
	else
		var->fdout = var->pipex[var->exec][1];
	if (ft_strcmplen(var->redir, "<<") > 0)
		handle_heredoc(var);
	if (is_redir(var->redir[var->exec]))
		get_std_redir(var->redir[var->exec], var);
}

void	ft_secur_fd(t_m *var)
{
	ft_unlink(var->redir, var->exec);
	if (var->fdin != 0 && var->fdin != -1)
		close((*var).fdin);
	if (var->fdout != 1 && var->fdout != -1)
		close((*var).fdout);
}

void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid)
{
	ft_init_fd_redir(var);
	if (is_env_builtin(var->cmd[0]) && var->tablen == 1 \
	&& do_builtin(var, var->cmd[0]) != INT_MIN)
		return ;
	ft_signal(4);
	(*pid) = fork();
	if ((*pid) == -1)
		return (free_child(var), write(2, "Error fork\n", 12) \
		, ft_fork_fail(var));
	if ((*pid) == 0)
	{
		if (var->fd_status_in == 1 || var->fd_status_out == 1)
			return (ft_close_pipe_fd(var), free_child(var), exit(1));
		ft_signal(5);
		dup2(var->fdin, 0);
		dup2(var->fdout, 1);
		ft_close_pipe_fd(var);
		if (do_builtin(var, (*var).cmd[var->exec]) == -1)
		{
			ft_init_arg(arg, var);
			ft_execve((*var).arg, targ, (*var).env, var);
		}
		return (free_child(var), ft_fork_fail(var), exit(g_exit_status));
	}
	ft_secur_fd(var);
}
