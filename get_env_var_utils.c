/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:57:44 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 21:15:15 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *env, char *envp)
{
	int	i;
	int	size;
	int	j;

	j = 0;
	i = 0;
	size = ft_strlen(envp);
	while (envp[i])
	{
		if (envp[i] && envp[i] == '=')
		{
			i++;
			while (envp[i] && i <= size)
			{
				env[j++] = envp[i++];
			}
		}
		if (envp[i])
			i++;
	}
	return (env);
}

int	is_in_env(char **envp, char *str, int end, int start)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp_env(str, envp[i], end, start) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strncmp_env(char *s1, char *s2, int n, int i)
{
	int	j;

	j = 0;
	while (((s1[i] != '\0') && (i < n)) || ((s2[j] != '\0') && (i < n)))
	{
		if (s1[i] != s2[j])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		}
		i++;
		j++;
	}
	if (s2[j] != '=')
		return (1);
	return (0);
}

int	ft_strlenenv(char *envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[i])
	{
		if (envp[i] && envp[i] == '=')
		{
			while (envp[i])
			{
				len++;
				i++;
			}
		}
		if (envp[i])
		i++;
	}
	return (len - 1);
}
