/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:28:56 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/17 14:55:14 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_underscore_env(char *str, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(str, tab[i], 2) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export_add_underscore(t_m *var, char *args)
{
	int		i;
	char	**tmp;

	i = ft_tablen((*var).env);
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (printf("malloc error\n"), exit(1));
	tmp[i + 1] = 0;
	i = 0;
	while ((*var).env[i])
	{
		tmp[i] = (*var).env[i];
		i++;
	}
	tmp[i] = ft_strdup(args);
	free(args);
	free((*var).env);
	(*var).env = tmp;
}

int	update_last_env(t_m *var)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!var->cmd || !var->cmd[i] || !var->cmd[i][j])
	{
		return (0);
	}
	while (var->cmd[i])
	{
		j = 0;
		while (var->cmd[i][j])
			j++;
		i++;
	}
	if (is_underscore_env("_=", var->env) == 0)
		export_env("_=", var->cmd[i - 1][j - 1], var);
	else
		ft_export_add_underscore(var, ft_strjoin("_=", var->cmd[i - 1][j - 1]));
	return (1);
}
