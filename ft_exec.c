/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:56:23 by chillion          #+#    #+#             */
/*   Updated: 2022/11/26 17:58:02 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *pcmd, char **option, char **envp, t_m *var)
{
	if (execve(pcmd, option, envp) == -1)
	{
		write(2, "AFTER EXEC\n", 12);
		ft_printf("%s\n", strerror(errno));
		if ((var->exec + 1) != (var->tablen - 1) )
			close((*var).pipex[1]);
		free((*var).arg);
		ft_free_split((*var).split_path);
		exit(127);
	}
}

void	ft_arg_with_path(char *arg, int *cmd)
{
	int	fd;

	(*cmd) = 0;
	fd = open(arg, O_RDWR);
	if ((fd == -1) && (errno == EISDIR))
	{
		ft_putstr_fd(arg, 2);
		write(2, ": Is a directory\n", 18);
		(*cmd) = -3;
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

int	ft_check_access(char *argv, char **split)
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
		i = 0;
		while (argv[i] && argv[i] != ' ')
		{
			write(2, &argv[i], 1);
			i++;
		}
		write(2, ": command not found\n", 21);
		return (-2);
	}
	return (i);
}