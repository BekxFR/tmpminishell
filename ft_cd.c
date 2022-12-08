/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/07 17:42:40 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Subject : Reproduction of cd function
It handles :
- cd par des chemins relatifs (cd .., cd dir_after)
- cd par chemin absolu

*/

int	find_env_name_line(char *name, char **env)
{
	int i;

	i = 0;
	while(env[i] && ft_strncmp(name, env[i], 4) != 0)
	{
		i++;
	}
	return (i);	
}

int	export_env(char *name, char *word, t_m *var)
{
	int line;
	(void)word;
	line = find_env_name_line(name, var->env);
	var->env[line] = ft_strjoin(name, word);
	return(line);
}

int ft_cd(char **cmd, int i, t_m *var)
{
	char	*path;
	char	*newpath;
	int		len;
		
	path = NULL;
	newpath = NULL;
	path = getcwd(path, 0);
	len = ft_tablen(cmd);
	if (len == 1)
		return (write(2, "cd only not handled\n", 21), 130);
	if (len > 2)
		return (write(2, "cd: too many arguments\n", 23), 130);
	if (cmd[i][0] != '/')
	{
		path = ft_strjoin_free(path, "/");
		path = ft_strjoin_free(path, cmd[i]);
		if (chdir(path) != 0)
			printf("cd: %s No such file or directory\n", cmd[i]);
	}
	else 
	{
		if (chdir(cmd[i]) != 0)
			printf("cd: %s No such file or directory\n", cmd[i]);
	}
	newpath = getcwd(newpath, 0);
	var->line = export_env("PWD=", newpath, var);
	return (0);
}