/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 16:54:43 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_name_line(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(name, env[i], ft_strlen(name)) != 0)
	{
		i++;
	}
	return (i);
}

int	export_env(char *name, char *word, t_m *var)
{
	int	line;

	line = find_env_name_line(name, var->env);
	var->env[line] = ft_strjoin(name, word);
	return (0);
}

char	*import_user(char *name, t_m *var)
{
	int	line;

	line = find_env_name_line(name, var->env);
	return (&var->env[line][5]);
}

int	cd_need_path(char **cmd, int len, t_m *var, char *newpath)
{
	if (len == 1 || (cmd[1] && cmd[1][0] == '~' && !cmd[2]))
	{
		newpath = import_user("HOME=", var);
		if (chdir(newpath) != 0)
			return (printf("cd : HOME not set\n"), 0);
		return (0);
	}
	if (len > 2)
		return (write(2, "cd: too many arguments\n", 23), 0); //130
	return (1);
}

int	ft_cd(char **cmd, int i, t_m *var)
{
	char	*path;
	char	*newpath;

	path = NULL;
	newpath = NULL;
	if (!cd_need_path(cmd, ft_tablen(cmd), var, newpath))
		return (0);
	path = getcwd(path, 0);
	if (!path)
		return (printf("chdir: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n"), 2);
	export_env("OLDPWD", path, var);
	if (cmd[1][0] != '/')
	{
		path = ft_strjoin_free(path, "/");
		path = ft_strjoin_free(path, cmd[i]);
		if (chdir(path) != 0)
			printf("cd: %s No such file or directory\n", cmd[i]);
	}
	else if (chdir(cmd[1]) != 0)
		printf("cd: %s No such file or directory\n", cmd[i]);
	newpath = getcwd(newpath, 0);
	export_env("PWD=", newpath, var);
	return (0);
}
