/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:44:01 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 15:12:38 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Subject : reproduction of echo function 

It handles several cases :
echo -n XXX
echo -nnnnnn (which works the same as echo -n) (no matter the number of n)
echo -nXXXX (which)
echo XXXXX
echo $USER (printf handle this behaviour)
echo '$USER'
echo "$USER"

*/

int	is_n_option(char *str)
{
	int	i;

	i = 0;
	
	if (str[i++] != '-')
		return (0);
	if (str[i++] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int i;
	
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	while (is_n_option(cmd[i]))
		i++;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (is_n_option(cmd[1]))
		write(1, "", 0);
	else if (!is_n_option(cmd[1]))
		write(1, "\n", 1);
	return (0);
}
