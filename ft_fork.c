/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:31:02 by chillion          #+#    #+#             */
/*   Updated: 2022/11/28 11:29:11 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork_fail(t_m *var)
{
	if ((*var).arg)
		free((*var).arg);
	if ((*var).split_path)
		ft_free_split((*var).split_path);
	if (((*var).fd1))
		close((*var).fd1);
	if ((*var).fd2)
		close((*var).fd2);
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
	(*pid) = fork();
	if ((*pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((*pid) == 0)
	{
		ft_init_arg(arg, var); // init arg
		ft_execve((*var).arg, targ, (*var).env, var); // char *, char **, char **, int
	}
}

void	ft_do_pipe_fork(t_m *var, char *arg, char **targ, int *pid)
{
	if (pipe((*var).pipex) == -1)
		return (write(2, "Error with pipe\n", 17), ft_fork_fail(var));
	(*pid) = fork();
	if ((*pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((*pid) == 0)
	{
		ft_init_arg(arg, var);
		close((*var).pipex[0]);
		if ((var->exec + var->tabexec + 1) != (var->tablen - 1) && (var->exec + var->tabexec) != (var->tablen - 1))
			dup2((*var).pipex[1], 1); // dup2 sauf pour le dernier exec
		close((*var).pipex[1]);
		ft_execve((*var).arg, targ, (*var).env, var); // char *, char **, char **, pipe
	}
	else
	{
		close((*var).pipex[1]);
		dup2((*var).pipex[0], 0);
		close((*var).pipex[0]);
	}
}
