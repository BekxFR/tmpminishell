/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:07:52 by chillion          #+#    #+#             */
/*   Updated: 2022/12/08 17:42:45 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_m *var, char **cmd)
{
	if (cmd[1])
		ft_export_with_arg(var, cmd);
	if (!cmd[1])
		get_exprt(var->env);
}

void	ft_export_with_arg(t_m *var, char **args)
{
	int	egalen;

	egalen = 0;
	while (*args)
	{
		egalen = ft_export_check_addargs(*args, &egalen);
		if (egalen > 0)
			return (ft_add_export_check_double(var, *args, egalen));
		if (egalen != -1 && ft_export_check_args(*args, &egalen))
			ft_export_check_double(var, *args, egalen);
		args++;
	}
}

void	ft_add_export_check_double(t_m *var, char *args, int egalen)
{
	int		i;

	i = 0;
	while ((*var).env[i])
	{
		if (!ft_strncmp((*var).env[i], args, (egalen)))
		{
			if (var->env[i][egalen] == '=')
			{
				(*var).env[i] = \
				ft_strjoin_free((*var).env[i], (args + (egalen + 2)));
				return ;
			}
		}
		i++;
	}
	ft_export_add(var, args, 1);
}

void	ft_export_check_double(t_m *var, char *args, int egalen)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*var).env[i])
	{
		if (!ft_strncmp((*var).env[i], args, (egalen + 1)))
		{
			free((*var).env[i]);
			tmp = ft_strdup(args);
			(*var).env[i] = tmp;
			return ;
		}
		i++;
	}
	ft_export_add(var, args, 0);
}

void	ft_export_add(t_m *var, char *args, int type)
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
	if (type == 0)
		tmp[i] = ft_strdup(args);
	if (type == 1)
		tmp[i] = ft_strdup_without_one(args);
	free((*var).env);
	(*var).env = tmp;
}
