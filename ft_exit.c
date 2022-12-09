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

void	ft_exit(t_m *var, char **cmd)
{
	if (var->tablen > 1)
		return ;
	if (is_str_digit(cmd[1]) && cmd[2])
	{
		write(1, "exit: too many arguments\n", 25); // voir s'il faut modifier le numero std
		var->status = 1;
		return ;
	}
	else if (cmd[1] && !is_str_digit(cmd[1]))
	{
		printf("exit : %s: numeric argument required\n", cmd[1]);
		free_all(var);
		exit(2);
	}
	else if (!cmd[1] && free_all(var))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{
		free_all(var);
		exit (ft_atoi(cmd[1]));
	}
}
