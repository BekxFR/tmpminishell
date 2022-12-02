/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:31:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 12:20:58 by mgruson          ###   ########.fr       */
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
		i++;
	}
	return (env);
}

char	*add_good_env(char *str, int end, int start, char *envp)
{
	t_index	i;
	char	*newstring;
	char	*env;

	i = initialize_index();
	i.count = end - start;
	i.len = ft_strlen(str) - (i.count + 1) + ft_strlenenv(envp);
	env = ft_calloc(sizeof(char), (ft_strlenenv(envp) + 1));
	env = get_env(env, envp);
	(void)i;
	newstring = ft_calloc(sizeof(char), (i.len + 1));
	while (str[i.i1])
	{
		while (str[i.i1] && i.i1 != (start - 1))
			newstring[i.i2++] = str[i.i1++];
		while (env[i.i3])
			newstring[i.i2++] = env[i.i3++];
		i.i1 = i.i1 + i.count + 1;
		while (str[i.i1])
			newstring[i.i2++] = str[i.i1++];
	}
	free(env);
	free(str);
	return (newstring);
}

char	*remove_wrong_env(char *str, int end, int start)
{
	t_index	i;
	char	*newstring;

	i = initialize_index();
	i.count = end - start;
	i.len = ft_strlen(str) - (i.count + 1);
	(void)i;
	newstring = ft_calloc(sizeof(char), (i.len + 1));
	while (str[i.i1])
	{
		while (str[i.i1] != '$')
			newstring[i.i2++] = str[i.i1++];
		i.i1 = i.i1 + i.count + 1;
		while (str[i.i1])
			newstring[i.i2++] = str[i.i1++];
	}
	free(str);
	return (newstring);
}

char	*new_env_var(char *str, char **envp, t_index i)
{
	while (str[i.i])
	{
		if (str[i.i] == '$' && ft_isalpha(str[i.i + 1]) > 0 \
		&& !is_in_simple_quote(str, i.i))
		{						
			i.start = ++i.i;
			while (str[i.i] && str[i.i] != ' '\
			&& str[i.i] != 39 && str[i.i] != 34 && str[i.i] != '$')
				i.end = ++i.i;
			i.j = is_in_env(envp, str, i.end, i.start);
			printf("test i.j %i\n", i.j);
			if (i.j > -1)
			{
				str = add_good_env(str, i.end, i.start, envp[i.j]);
				i.i = i.start - 2 + ft_strlenenv(envp[i.j]);
			}
			else
			{
				str = remove_wrong_env(str, i.end, i.start);
				i.i = i.start - 2;
			}
			i.j = 0;
		}
		i.i++;
	}
	return (str);
}

char	**get_env_var(char **args, char **envp)
{
	t_index	i;
	t_index	a;

	i = initialize_index();
	a = initialize_index();
	while (args[i.i])
	{
		args[i.i] = new_env_var(args[i.i], envp, a);
		i.i++;
	}
	return (args);
}
