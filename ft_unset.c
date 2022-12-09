/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:28:16 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 17:36:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_m *var, char **args)
{
	int	egalen;

	egalen = 0;
	if (!args[1])
		return ;
	else
	{
		while (*args)
		{
			if (ft_unset_check_args(*args, &egalen))
				ft_unset_check_double(var, *args, egalen);
			args++;
		}
	}
}

void	ft_unset_check_double(t_m *var, char *args, int egalen)
{
	int		i;

	i = 0;
	while ((*var).env[i])
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
	int		i;
	int		j;
	char	**tmp;

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
