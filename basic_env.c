/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:48:23 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 21:48:40 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (free(env), free(str), newstring);
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
	return (free(str), newstring);
}

char	*basic_env(char *str, char **envp, t_index *i)
{
	i->start = ++i->i;
	while (str[i->i] && (isalnum(str[i->i]) || str[i->i] == '_'))
		i->end = ++i->i;
	i->j = is_in_env(envp, str, i->end, i->start);
	if (i->j > -1)
	{
		str = add_good_env(str, i->end, i->start, envp[i->j]);
		i->i = i->start - 1;
	}
	else
	{
		str = remove_wrong_env(str, i->end, i->start);
		i->i = i->start - 1;
	}
	i->j = 0;
	return (str);
}
