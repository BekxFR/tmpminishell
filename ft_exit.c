/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/16 17:04:29 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_exit_1(t_m *var)
{
	g_exit_status = 1;
	write(2, "exit: too many arguments\n", 25);
	if (var->tablen > 1)
	{
		ft_close_pipe_fd(var);
		free_child(var);
		exit(1);
	}
	return ;
}

void	ft_exit(t_m *var, char **cmd)
{
	if (is_str_digit(cmd[1]) && ft_tablen(cmd) > 2)
		ft_exit_1(var);
	else if (cmd[1] && is_str_digit(cmd[1]) == 0)
	{
		write(2, "exit : ", 8);
		ft_putstr_fd(cmd[1], 2);
		write(2, ": numeric argument required\n", 29);
		ft_close_pipe_fd(var);
		free_child(var);
		exit(2);
	}
	else if (ft_tablen(cmd) == 1)
	{
		write(2, "exit\n", 5);
		ft_close_pipe_fd(var);
		free_child(var);
		exit(0);
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{	
		g_exit_status = ft_atoi(cmd[1]);
		ft_close_pipe_fd(var);
		free_child(var);
		exit (g_exit_status);
	}
}
