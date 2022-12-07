/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:24:46 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 17:37:35 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_simple_pointer(int count, int t, char **s1, t_m *var)
{
	s1[t] = (char *)ft_calloc((count + 1), sizeof(char));
	if (!s1[t])
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_error_doubletab(s1, t);
		write(2, "malloc error\n", 13);
		return (2);
	}
	return (0);
}

int	is_arg(char *s, int i)
{
	if ((s[i] != ' ' && s[i] != '|' && \
	s[i] != '<' && s[i] != '>' && s[i] != '\n') || \
	is_in_quote(s, i))
		return (1);
	return (0);
}

int	is_op(char *s, int i)
{
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		return (1);
	return (0);
}

int	malloc_args(char *s, char c, char **s1, t_m *var)
{
	t_index	i;

	i = initialize_index();
	while (s[i.i] && s[i.i] != '\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		while (is_op(s, i.i) && i.count++ > -1)
			i.i++;
		if (i.count != 0 && i.n++ > -2)
		{	
			if (malloc_simple_pointer(i.count, i.n, s1, var) == 2)
				return (2);
			i.count = 0;
		}
		while (s[i.i] && is_arg(s, i.i) && i.count++ > -1)
			i.i++;
		if (i.count != 0 && i.n++ > -2)
		{
			if (malloc_simple_pointer(i.count, i.n, s1, var) == 2)
				return (2);
			i.count = 0;
		}
	}
	return (0);
}
