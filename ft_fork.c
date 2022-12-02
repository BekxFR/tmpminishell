/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:31:02 by chillion          #+#    #+#             */
/*   Updated: 2022/12/02 18:36:42 by chillion         ###   ########.fr       */
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

void	ft_do_fork(t_m *var, char *arg, char **targ, int *pid)
{
	var->cmdtype = 1;
	var->fdin = 0;
	var->fdout = 0;
	if (ft_strcmplen(var->redir, "<<") > 0)
		handle_heredoc(var);
	if (pipe((*var).pipex) == -1)
		return (write(2, "Error with pipe\n", 17), ft_fork_fail(var));
	if (is_redir((*var).redir[0]))
		get_std_redir((*var).redir[0], var);
	ft_fd_init(var);
	(*pid) = fork();
	if ((*pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((*pid) == 0)
	{
		if (((var->exec + 1) == (var->tablen)) && (is_redir_out(var->redir[var->exec]) == 0))
		{
				write(2, "RRERE\n", 7);
				var->fdout = 1;
				// close(var->pipex[0]);
				close(var->pipex[1]);
		}
		dup2((*var).fdin, 0);
		if ((*var).fdout != 1)
			dup2((*var).fdout, 1);
		if (var->fdin != 0)
			close(var->fdin);
		if (var->fdout != 1)
			close(var->fdout);
		ft_init_arg(arg, var);
		ft_execve((*var).arg, targ, (*var).env, var);
	}
	else
	{
		if (var->fdin != 0)
			close(var->fdin);
		if (var->fdout != 1)
			close(var->fdout);
	}
}

void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	var->cmdtype = 0;
	var->fdin = 0;
	var->fdout = 0;
	if (ft_strcmplen(var->redir, "<<") > 0)
		handle_heredoc(var);
	if (pipe((*var).pipex) == -1)
		return (write(2, "Error with pipe\n", 17), ft_fork_fail(var));
	if (is_redir((*var).redir[var->exec]), var)
		get_std_redir((*var).redir[var->exec], var);
	ft_fd_init(var);
	(*pid) = fork();
	if ((*pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((*pid) == 0)
	{
		ft_init_arg(arg, var);
		// dup2((*var).fdin, 0);
		// if (((var->exec + 1) == (var->tablen)) && (is_redir_out(var->redir[var->exec]) == 0))
		// {
		// 		var->fdout = 1;
		// 		close(var->pipex[1]);
		// }
		// if ((*var).fdout != 1)
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (((var->exec + 1) != (var->tablen)) || (is_redir_out(var->redir[var->exec]) != 0))
			dup2((*var).fdout, 1);
		// if (var->fdin != 0)
		// 	close(var->fdin);
		// if (var->fdout != 1)
		// 	close(var->fdout);
		ft_execve((*var).arg, targ, (*var).env, var);
	}
	dup2((*var).fdin, 0);
	if (var->fdin != 0)
		close(var->fdin);
	if (var->fdout != 1)
		close(var->fdout);
}