/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:47 by chillion          #+#    #+#             */
/*   Updated: 2022/12/13 12:25:33 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*basic_env_heredoc(char *str, char **envp, t_index *i)
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

char	*new_env_var_heredoc(char *str, char **envp, t_m *var)
{
	t_index	i;
	char	*itoa;

	itoa = ft_itoa(g_exit_status);
	(void)var;
	i = initialize_index();
	while (str[i.i])
	{
		if (str[i.i] == '$' && ((ft_isalpha(str[i.i + 1]) > 0) || \
		str[i.i + 1] == '_'))
			str = basic_env_heredoc(str, envp, &i);
		if (str[i.i] == '$' && str[i.i + 1] == '?')
			str = get_status(str, (i.i + ft_intlen(g_exit_status) + 1), \
			(i.i + 1), itoa);
		if (str[i.i] == '$' && (ft_isdigit(str[i.i + 1]) > 0 \
		|| (str[i.i + 1] == 34 || str[i.i + 1] == 39)))
			str = exception_env(str, &i);
		if (str[i.i])
			i.i++;
	}
	return (free(itoa), str);
}

void	ft_heredoc_fd(t_m *var, int n)
{
	char	*str;
	int		quote;

	quote = !has_quote(var->comp);
	ft_signal(3);
	while (n > 0)
	{
		str = readline(">");
		if (g_exit_status == -42)
			return ;
		if (!str)
		{
			write(2, "warning: don't find end-of-file (wanted `", 42);
			ft_putstr_fd((*var).comp, 2);
			write(2, "')\n", 4);
			return ;
		}
		if (ft_strcmp(clear_quote((*var).comp), str) == 0)
			return ;
		if (quote == 1)
			str = new_env_var_heredoc(str, var->env, var);
		write((*var).fdin, str, ft_strlen(str));
		write((*var).fdin, "\n", 2);
		free(str);
	}
	return (ft_cleanheredoc_fd(NULL, str, (*var).comp, (*var).fdin));
}
