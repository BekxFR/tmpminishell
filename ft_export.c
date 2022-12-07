/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:07:52 by chillion          #+#    #+#             */
/*   Updated: 2022/12/05 16:30:15 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_m *var, char **cmd)
{
	if(cmd[1])
		ft_exportunset_with_arg(var, cmd, 1);
	if (!cmd[1])
		get_exprt(var->env);	
}

void	ft_exportunset_with_arg(t_m *var, char **args, int soft)
{
	int	egalen;

	egalen = 0;
	if (soft == 1)
	{
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
	if (soft == 2)
	{
		while (*args)
		{
			if (ft_unset_check_args(*args, &egalen))
				ft_unset_check_double(var, *args, egalen);
			args++;
		}
	}
}

void	ft_add_export_check_double(t_m *var, char *args, int egalen)
{
	int		i;

	i = 0;
	while((*var).env[i])
	{
		if (!ft_strncmp((*var).env[i], args, (egalen)))
		{
			if (var->env[i][egalen] == '=')
			{
				(*var).env[i] = ft_strjoin_free((*var).env[i], (args + (egalen + 2)));
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
	while((*var).env[i])
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

char	*ft_strdup_without_one(const char *src)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dest;

	j = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (j));
	if (!dest)
		return (NULL);
	dest[j - 1] = '\0';
	k = 0;
	while (src[k] && src[k] != '+')
		k++;
	i = 0;
	j = 0;
	while (src[i])
	{
		if (i == k)
			j++;
		dest[i] = src[i + j];
		i++;
	}
	return (dest);
}

void	ft_export_add(t_m *var, char *args, int type)
{
	int	i;
	char **tmp;

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

int	ft_export_check_args(char *args, int *egalen)
{
	if (!args && !*args)
		return (0);
	if ((ft_isalpha(args[0]) == 0) && args[0] != '_')
		return (printf("export: `%s': not a valid identifier\n", args), 0);
	*egalen = -1;
	while ((++*egalen) > -1 && args[(*egalen)] && (args[(*egalen) + 1] != '='))
	{
		if (args[*egalen] != '_' && (ft_isalnum(args[*egalen]) == 0))
			return (printf("export: `%s': not a valid identifier\n", args), 0);
	}
	if (args[*egalen] == '\0')
		return (0);
	return ((++*egalen));
}

int	ft_export_check_addargs(char *args, int *egalen)
{
	if (!args && !*args)
		return (0);
	if ((ft_isalpha(args[0]) == 0) && args[0] != '_')
		return (printf("export: `%s': not a valid identifier\n", args), -1);
	*egalen = -1;
	while ((++*egalen) > -1 && args[(*egalen)] && (args[(*egalen)] != '='))
	{
		if (args[(*egalen) + 1] == '=' && args[(*egalen)] == '+')
		{
			if (args[(*egalen) + 2] != '\0')
				return (*egalen);
		}
		if (args[*egalen] != '_' && (ft_isalnum(args[*egalen]) == 0))
			return (printf("export: `%s': not a valid identifier\n", args), -1);
	}
	if (args[*egalen] == '\0')
		return (-1);
	return (0);
}
