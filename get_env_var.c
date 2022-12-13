/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:31:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 10:43:34 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*exception_env(char *str, t_index *i)
{
	if (ft_isdigit(str[i->i + 1]))
		str = ft_strcpy(&str[i->i], &str[i->i + 2]);
	else
		str = ft_strcpy(&str[i->i], &str[i->i + 1]);
	str = clear_quote(&str[i->i]);
	return (str);
}

char	*new_env_var(char *str, char **envp)
{
	t_index	i;
	char	*itoa;

	itoa = ft_itoa(g_exit_status);
	i = initialize_index();
	while (str[i.i])
	{
		if (str[i.i] == '$' && ((ft_isalpha(str[i.i + 1]) > 0) || \
		str[i.i + 1] == '_') && !is_in_simple_quote(str, i.i))
			str = basic_env(str, envp, &i);
		if (str[i.i] == '$' && str[i.i + 1] == '?' \
		&& !is_in_simple_quote(str, i.i))
			str = get_status(str, (i.i + ft_intlen(g_exit_status) + 1), \
			(i.i + 1), itoa);
		if (str[i.i] == '$' && (ft_isdigit(str[i.i + 1]) > 0 \
		|| (str[i.i + 1] == 34 || str[i.i + 1] == 39)) \
		&& !is_in_simple_quote(str, i.i))
			str = exception_env(str, &i);
		if (str[i.i])
			i.i++;
	}
	return (free(itoa), str);
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
