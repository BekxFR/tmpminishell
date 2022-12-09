/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:31:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 17:35:39 by mgruson          ###   ########.fr       */
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

char	*basic_env(char *str, char **envp, t_index *i)
{
	i->start = ++i->i;
	while (str[i->i] && (isalnum(str[i->i]) || str[i->i] == '_'))
		i->end = ++i->i;
	i->j = is_in_env(envp, str, i->end, i->start);
	if (i->j > -1)
	{
		str = add_good_env(str, i->end, i->start, envp[i->j]);
		i->i = i->start - 2;
	}
	else
	{
		str = remove_wrong_env(str, i->end, i->start);
		i->i = i->start - 2;
	}
	i->j = 0;
	return (str);
}

char	*new_env_var(char *str, char **envp)
{
	t_index	i;

	i = initialize_index();
	while (str[i.i])
	{
		if (str[i.i] == '$' && ((ft_isalpha(str[i.i + 1]) > 0) || \
		str[i.i + 1] == '_') && !is_in_simple_quote(str, i.i))
			str = basic_env(str, envp, &i);
		if (str[i.i] == '$' && str[i.i + 1] == '?' \
		&& !is_in_simple_quote(str, i.i))
		{
			str = get_status(str, (i.i + 2), (i.i + 1), "2"); // "2" a remplacer par la variable status
			i.i = i.i - 1 + ft_intlen(2);
		}
		if (str[i.i] == '$' && (ft_isdigit(str[i.i + 1]) > 0 \
		|| (str[i.i + 1] == 34 || str[i.i + 1] == 39)) \
		&& !is_in_simple_quote(str, i.i))
		{	
			str = ft_strcpy(&str[i.i], &str[i.i + 1]);
			str = clear_quote(&str[i.i]);
		}
		i.i++;
	}
	return (str);
}

char	**get_env_var(char **args, char **envp)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		if ((args[i.i] && i.i == 0) || (i.i >= 1 && \
		!ft_strcmp(args[i.i - 1], "<<") == 0))
			args[i.i] = new_env_var(args[i.i], envp);
		i.i++;
	}
	return (args);
}
