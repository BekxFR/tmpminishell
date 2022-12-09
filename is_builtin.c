/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:03:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 18:55:31 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (ft_isdigit(str[i]) != 0 || str[i] != '-' || str[i] != '+')
		return (0);	
	i++;
	while (ft_isdigit(str[i]) != 0)
		i++;
	if ((int)str[i] == 0)
		return (1);
	return (0);
}

int	do_builtin(t_m *var, char **cmd)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(var, cmd), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0 && go_in_builtin(cmd[1]) == 1)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, 1, var), 1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(var, cmd), 1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(var, cmd), 1);
	if (ft_strcmp(cmd[0], "env") == 0 && !cmd[1])
		return (ft_env(var->env), 1);
	return (0);
}

int	is_env_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}
