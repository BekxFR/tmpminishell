/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:32:21 by chillion          #+#    #+#             */
/*   Updated: 2022/12/16 15:05:37 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork_fail(t_m *var)
{
	if ((*var).arg)
		free((*var).arg);
	if ((*var).split_path)
		ft_free_split((*var).split_path);
	if (var->fdin > 2)
		close((*var).fdin);
	if (var->fdout > 2)
		close((*var).fdout);
}

void	ft_arg_check_fullpath(char *arg, t_m *var)
{
	ft_arg_with_path(arg, &(*var).pcmd_line, var);
	if (!var->path && var->pcmd_line != -1)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_close_pipe_fd(var);
		free_child(var);
		exit(127);
	}
	if ((*var).pcmd_line == 0)
	{
		(*var).split_path = ft_split((*var).path, ':');
		ft_add_arg_totchar((*var).split_path, arg, '/');
	}
}

void	ft_init_arg(char *argv, t_m *var)
{
	(*var).path = ft_init_path_var((*var).env);
	ft_arg_check_fullpath(argv, var);
	if ((*var).pcmd_line == 0)
	{
		(*var).pcmd_line = ft_check_access(argv, (*var).split_path, var);
		if ((*var).pcmd_line == -2)
			return (ft_close_pipe_fd(var), free_child(var), \
			ft_free_split((*var).split_path), exit(127));
		else
			(*var).arg = (*var).split_path[(*var).pcmd_line];
		ft_free_split_exclude_line((*var).split_path, (*var).pcmd_line);
		(*var).split_path = ft_split(argv, ' ');
	}
	else if ((*var).pcmd_line != -3)
	{
		(*var).arg = ft_strdup(argv);
		(*var).split_path = ft_split(argv, ' ');
		(*var).pcmd_line = -1;
	}
}

void	ft_close_pipe_fd(t_m *var)
{
	int	i;

	i = 0;
	while (var->pipex[i])
	{
		if (var->pipex[i][0] > 2)
			close(var->pipex[i][0]);
		if (var->pipex[i][1] > 2)
			close(var->pipex[i][1]);
		i++;
	}
	if (var->fdin > 2)
		close((*var).fdin);
	if (var->fdout > 2)
		close((*var).fdout);
}
