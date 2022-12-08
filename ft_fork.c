/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:31:02 by chillion          #+#    #+#             */
/*   Updated: 2022/12/07 17:39:21 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork_fail(t_m *var)
{
	if ((*var).arg)
		free((*var).arg);
	if ((*var).split_path)
		ft_free_split((*var).split_path);
	if (((*var).fdin))
		close((*var).fdin);
	if ((*var).fdout)
		close((*var).fdout);
}

void	ft_arg_check_fullpath(char *arg, t_m*var)
{
	ft_arg_with_path(arg, &(*var).pcmd_line); //arg == command[0] - pcmd_line == -3 si directory ou -1 si full path
	if ((*var).pcmd_line == 0) // si non full path
	{
		(*var).split_path = ft_split((*var).path, ':'); //split_path = l'ensemble des chemins de PATH=
		ft_add_arg_totchar((*var).split_path, arg, '/'); /* all path + / + arg == /usr/bin + / + echo */
		// free((*var).arg); // free arg;
	}
}

void	ft_init_arg(char *argv, t_m *var)
{
	(*var).path = ft_init_path_var((*var).env); // init path = texte apres env => PATH=""
	ft_arg_check_fullpath(argv, var); // check full path
	if ((*var).pcmd_line == 0) // si non full path
	{
		(*var).pcmd_line = ft_check_access(argv , (*var).split_path); // check la bonne ligne et keep ligne
		if ((*var).pcmd_line == -2)
			(*var).arg = strdup(argv); // si aucune ligne on recup la commande seule
		else
			(*var).arg = (*var).split_path[(*var).pcmd_line]; // si ligne ok arg == bonne ligne ex : /usr/bin/echo
		ft_free_split_exclude_line((*var).split_path, (*var).pcmd_line); // free reste du char ** de path
		(*var).split_path = ft_split(argv, ' '); // split de argv == char ** ex : ["ls","- la"]
	}
	else if ((*var).pcmd_line != -3) // si full path
	{
		(*var).split_path = ft_split(argv, ' '); // split de argv == char ** ex : ["/usr/bin/ls","- la"]
		(*var).pcmd_line = -1;
	}
}

void	ft_close_pipe_fd(t_m *var)
{
	int	i;

	i = 0;
	while(var->pipex[i])
	{
		if (var->pipex[i][0] != 0)
			close(var->pipex[i][0]);
		if (var->pipex[i][1] != 1)
			close(var->pipex[i][1]);
		i++;
	}
}

void	ft_init_fd_redir(t_m *var)
{
	if (var->exec == 0)
		var->fdin = 0;
	else
		var->fdin = var->pipex[var->exec - 1][0];
	if((var->exec + 1) == (var->tablen))
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

void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid)
{
	ft_init_fd_redir(var);
	if (is_env_builtin(var->cmd[0]) && var->tablen == 1) 
	{
		do_builtin(var, var->cmd[0]);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	(*pid) = fork();
	if ((*pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((*pid) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(var->fdin, 0);
		dup2(var->fdout, 1);
		ft_close_pipe_fd(var);
		if (!do_builtin(var, (*var).cmd[var->exec]))
		{
			ft_init_arg(arg, var);
			ft_execve((*var).arg, targ, (*var).env, var);
		}
		exit (127);
	}
	ft_unlink(var->redir, var->exec);
	if (var->fdin != 0)
		close(var->fdin);
	if (var->fdout != 1)
		close(var->fdout);
	return ;
}