/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 10:44:52 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Subject : Reproduction of cd function
It handles :
- cd par des chemins relatifs (cd .., cd dir_after)
- cd par chemin absolu

*/

int ft_cd(char **cmd, int i)
{
	char	*path;
	char	*newpath;
		
	path = NULL;
	newpath = NULL;
	path = getcwd(path, 0);
	printf("%s\n", path);
	if (!cmd[i])
	{
		printf("handle later\n");
		return (0);
	}
	if (cmd[i][0] != '/')
	{
		path = ft_strjoin_free(path, "/");
		path = ft_strjoin_free(path, cmd[i]);
		if (chdir(path) != 0)
			printf("Error\n");
		printf("%s\n", path);
	}
	else 
	{
		if (chdir(cmd[i]) != 0)
			printf("Error\n");
		printf("test\n");
	}
	printf("c1\n");
	newpath = getcwd(newpath, 0);
	printf("%s\n", newpath);
	return (0);
}