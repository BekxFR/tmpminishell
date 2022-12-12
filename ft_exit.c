/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 19:28:31 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

void	ft_exit(t_m *var, char **cmd)
{
	if (is_str_digit(cmd[1]) && ft_tablen(cmd) > 2)
	{
		exit_status = 1;
		write(2, "exit: too many arguments\n", 25);
		if (var->tablen > 1)
		{
			free_child(var);	
			exit(1);
		}
		return ;
	}
	else if (cmd[1] && is_str_digit(cmd[1]) == 0)
	{
		write(2, "exit : ", 8);
		ft_putstr_fd(cmd[1], 2);
		write(2, ": numeric argument required\n",29);
		free_child(var);
		exit(2);
	}
	else if (ft_tablen(cmd) == 1)
	{
		write(2, "exit\n", 5);
		free_child(var);
		exit(0);
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{	
		exit_status = ft_atoi(cmd[1]);
		free_child(var);
		exit (exit_status);
	}
}


