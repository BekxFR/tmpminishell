/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:14:54 by chillion          #+#    #+#             */
/*   Updated: 2022/11/24 18:55:37 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_check_double(t_m *var, char *args, int egalen)
{
	int		i;

	i = 0;
	while((*var).env[i])
	{
		if (!ft_strncmp((*var).env[i], args, egalen) \
		&& ft_len_beforechar((*var).env[i], '=') == egalen)
		{
			ft_unset_remove(var, i);
			return ;
		}
		i++;
	}
}

void	ft_unset_remove(t_m *var, int m)
{
	int	i;
	int	j;
	char **tmp;

	i = ft_tablen((*var).env);
	tmp = (char **)malloc(sizeof(char *) * (i));
	if (!tmp)
		return (printf("malloc error\n"), exit(1));
	tmp[i - 1] = 0;
	j = 0;
	i = 0;
	while ((*var).env[i])
	{
		if (i == m)
		{
			free((*var).env[i]);
			j = 1;
		}
		else
			tmp[i - j] = (*var).env[i];
		i++;
	}
	free((*var).env);
	(*var).env = tmp;
}

int	ft_unset_check_args(char *args, int *egalen)
{
	if (!args && !*args)
		return (0);
	if ((ft_isalpha(args[0]) == 0) && args[0] != '_')
		return (0);
	*egalen = -1;
	while ((++*egalen) > -1 && args[(*egalen)])
	{
		if (args[*egalen] != '_' && (ft_isalnum(args[*egalen]) == 0))
			return (0);
	}
	return (*egalen);
}

void	ft_print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	ft_env(t_m *var, char **envp)
{
	int i;
	
	if (!envp)
	{
		write(2, "NO ENV\n", 8);
		(*var).env = (char **)malloc(sizeof(char *) * 1);
		if (!(*var).env)
			return (-1);
		(*var).env[0] = (char *)malloc(sizeof(char) * 1);
		if (!(*var).env[0])
			return (free((*var).env), -1);
		(*var).env[0][0] = 0;
		return (1);
	}
	i = 0;
	while (envp[i])
		i++;
	(*var).env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*var).env)
		return (-1);
	(*var).env[i] = 0;
	i = -1;
	while (envp[++i])
		(*var).env[i] = ft_strdup(envp[i]);
	return (0);
}
