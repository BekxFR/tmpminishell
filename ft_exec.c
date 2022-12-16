/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:56:23 by chillion          #+#    #+#             */
/*   Updated: 2022/12/16 15:08:20 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_execve(char *pcmd, char **option, char **envp, t_m *var)
{
	struct stat	buff;

	execve(pcmd, option, envp);
	if (stat(pcmd, &buff) == 0)
	{
		if (pcmd[ft_strlen(pcmd) - 1] == '/')
		{
			ft_close_pipe_fd(var);
			free_child(var);
			free((*var).arg);
			ft_free_split((*var).split_path);
			exit (0);
		}
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, pcmd, ft_strlen(pcmd));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		ft_close_pipe_fd(var);
		free_child(var);
		free((*var).arg);
		ft_free_split((*var).split_path);
		exit(126);
	}
	return (ft_close_pipe_fd(var), free_child(var), free((*var).arg), \
	ft_free_split((*var).split_path), exit(127));
}

void	ft_arg_with_path(char *arg, int *cmd, t_m *var)
{
	int	fd;

	(*cmd) = 0;
	fd = open(arg, O_RDWR);
	if ((fd == -1) && (errno == EISDIR))
	{
		ft_putstr_fd(arg, 2);
		write(2, ": Is a directory\n", 18);
		ft_close_pipe_fd(var);
		free_child(var);
		exit(126);
		(*cmd) = -3;
		return ;
	}
	if (arg && ft_strlen(arg) > 2)
	{
		if (arg[0] != '.' && arg[0] != '/' && arg[1] != '/')
			return ;
	}
	if (fd != -1)
		close(fd);
	fd = access(arg, X_OK);
	if (fd == 0)
		(*cmd) = -1;
}

void	ft_add_arg_totchar(char **str, char *arg, char c)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = ft_strlen(str[i]) + ft_strlen(arg) + 2;
		tmp = (char *)malloc(sizeof(char) * j);
		if (!tmp)
			return ;
		j = -1;
		while (str[i][++j])
			tmp[j] = str[i][j];
		tmp[j] = c;
		k = -1;
		while (arg[++k])
			tmp[++j] = arg[k];
		tmp[++j] = '\0';
		free(str[i]);
		str[i] = tmp;
		i++;
	}
}

int	ft_check_access(char *argv, char **split, t_m *var)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (split[i] && fd != 0)
	{
		fd = access(split[i], X_OK);
		if (fd == 0)
			return (i);
		i++;
	}
	if (fd == -1)
	{
		ft_putstr_fd(argv, 2);
		if (var->cmd[var->exec][0][0] == '/')
			write(2, ": No such file or directory\n", 29);
		else
			write(2, ": command not found\n", 21);
		return (-2);
	}
	return (i);
}
