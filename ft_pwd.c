/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:09 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 17:40:35 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_in_builtin(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (ft_strcmp(str, "-L") == 0 || ft_strcmp(str, "-P") == 0 \
	|| ft_strcmp(str, "-LP") == 0)
		return (0);
	while (str[i] == '-' && i < 2)
		i++;
	if (isprint(str[i]))
		return (0);
	return (1);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("pwd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n");
		return (2);
	}
	else
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
	}
	return (0);
}
