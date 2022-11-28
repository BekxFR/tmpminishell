/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:57:44 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/23 17:28:36 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
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
	int	size;

	i = 0;
	len = 0;
	size = ft_strlen(envp);
	while (envp[i])
	{
		if (envp[i] && envp[i] == '=')
		{
			while (envp[i] && i <= size)
			{
				len++;
				i++;
			}
		}
		i++;
	}
	return (len - 1);
}
