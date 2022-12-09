/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:47 by chillion          #+#    #+#             */
/*   Updated: 2022/12/09 14:07:23 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*basic_env_heredoc(char *str, char **envp, t_index *i)
{
		i->start = ++i->i;
		while (str[i->i] && isalnum(str[i->i]))
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

char	*new_env_var_heredoc(char *str, char **envp, t_m *var)
{
	t_index	i;

	(void)var;
	i = initialize_index();
	while (str[i.i])
	{
		if (str[i.i] == '$' && ft_isalpha(str[i.i + 1]) > 0)
			str = basic_env_heredoc(str, envp, &i);
		if (str[i.i] == '$' && str[i.i + 1] == '?')
		{
			str = get_status(str, (i.i + 2), (i.i + 1), "2"); // "2" a remplacer par la variable status
			i.i = i.i - 1 + ft_intlen(2);
		}
		if (str[i.i] == '$' && ft_isdigit(str[i.i + 1]) > 0)
		{	
			str = ft_strcpy(&str[i.i], &str[i.i + 1]);
			str = clear_quote(&str[i.i]);
		}
		i.i++;
	}
	return (str);
}

void	ft_heredoc_fd(t_m *var, int n)
{
	char	*str;
	int		quote;

	(void)n;
	quote = !has_quote(var->comp);
	ft_signal(3);
	while (n > 0)
	{
		str = readline(">");
		if (!str)
		{
			write(2, "warning: don't find end-of-file (wanted `", 42);
			ft_putstr_fd((*var).comp, 2);
			write(2, "')\n", 4);
			return ;
		}
		if (ft_strcmp(clear_quote((*var).comp), str) == 0)
			return ;
		printf("cmp : %s\n", (*var).comp);
		if (quote == 1)
			str = new_env_var_heredoc(str, var->env, var);
		write((*var).fdin, str, ft_strlen(str));
		write((*var).fdin, "\n", 2);
	}
	return (ft_cleanheredoc_fd(NULL, str, (*var).comp, (*var).fdin));
}

void	ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, handle_sigint_1); /* ctrl + c  affiche un nouveau prompt */
		signal(SIGQUIT, SIG_IGN); /* ctrl + \  ne fait rien */
	}
	if (i == 2)
	{
		signal(SIGINT, handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 3)
	{
		signal(SIGINT, handle_sigint_3);
		signal(SIGQUIT, SIG_IGN);
	}
}
