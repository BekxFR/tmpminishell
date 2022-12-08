/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 19:29:41 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_m *var, char **cmd)
{
	if (var->tablen > 1)
		return ;
	if (is_str_digit(cmd[1]) && cmd[2] &&	free_all(var))
	{
		write(1, "exit: too many arguments\n", 25); // voir s'il faut modifier le numero std
		var->status = 1;
		// exit(var->status);
	}
	else if (cmd[1] && !is_str_digit(cmd[1]) &&	free_all(var))
	{   
		write(2, "exit : ", 8);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": numeric argument required\n", 26);
		var->status = 2;
		exit(var->status);
	}
	else if (!cmd[1] && free_all(var))
	{
		var->status = 0;
		write(1, "exit\n", 5);
		exit(var->status);
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{
		var->status = ft_atoi(cmd[1]);
		free_all(var);
		exit (var->status);
	}
}
