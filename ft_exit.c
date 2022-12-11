/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 12:12:56 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

void	ft_exit(t_m *var, char **cmd)
{
	if (var->tablen > 1)
		return ;
	if (!is_str_digit(cmd[1]) && cmd[2])
	{
		exit_status = 1;
		write(2, "exit: too many arguments\n", 25);
		if (var->tablen > 1)
			exit(1);
		return ;
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{
		write(2, "exit : ", 8);
		ft_putstr_fd(cmd[1], 2);
		write(2, ": numeric argument required\n",29);
		exit_status = 2;
		return (exit(2));
	}
	else if (!cmd[1] && free_all(var))
		return (write(2, "exit\n", 5), exit(0));
	else if (cmd[1] && !is_str_digit(cmd[1]))
	{
		// free_all(var);
		int i = ft_atoi(cmd[1]);
		if (var->redir)
			free_tripletab(var->redir);
		if (var->cmd)
			free_tripletab(var->cmd);
		if (var->env)
			free_doubletab(var->env);
		ft_free_inttab(var->pipex);
		if (var->pid)
			free(var->pid);
		rl_clear_history();
		// if (var->cmd)
		// 	free_tripletab2(var);
		// ft_puttripletab(var->cmd);
		exit (i);
	}
}
