/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 20:26:41 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
	free(var->env[line]);
	var->env[line] = ft_strjoin(name, word);
	return (0);
}

char	*import_user(char *name, t_m *var)
{
	int	line;

	line = find_env_name_line(name, var->env);
	if (line == ft_tablen(var->env))
		return (NULL);
	return (&var->env[line][5]);
}

int	cd_need_path(char **cmd, int len, t_m *var, char *newpath)
{
	if (len == 1 || (cmd[1] && cmd[1][0] == '~' && !cmd[2]))
	{
		newpath = import_user("HOME=", var);
		if (chdir(newpath) != 0)
		{
			g_exit_status = 1;
			return (write(2, "cd : HOME not set\n", 19), 0);
		}
		return (0);
	}
	if (len > 2)
	{
		g_exit_status = 1;
		return (write(2, "cd: too many arguments\n", 24), 0);
	}
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
		return (write(2, "No such file or directory\n", 27), 1);
	export_env("OLDPWD=", path, var);
	if (cmd[1][0] != '/')
	{
		path = ft_strjoin_free(path, "/");
		path = ft_strjoin_free(path, cmd[i]);
		if (chdir(path) != 0)
			return (free(path), write(2, "cd: ", 5), ft_putstr_fd(cmd[i], 2) \
			, write (2, " No such file or directory\n", 28), 1);
	}
	else if (chdir(cmd[1]) != 0)
		return (write(2, "cd: ", 5), ft_putstr_fd(cmd[i], 2) \
		, write (2, " No such file or directory\n", 28), 1);
	newpath = getcwd(newpath, 0);
	export_env("PWD=", newpath, var);
	return (free(path), free(newpath), 0);
}
