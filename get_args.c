/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:41:21 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 15:52:41 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_args(char *s, char c, char **s1)
{
	t_index i;

	i = initialize_index();
	while (s[i.i] && s[i.i] !='\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		i.l = 0;
		while ((s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|'))
		{	
			s1[i.t][i.l++] = s[i.i++];
		}
		if (i.l != 0 && i.t++ > -1)
			i.l = 0;	
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || is_in_quote(s, i.i)))
		{
			s1[i.t][i.l++] = s[i.i++];
		}
		if (i.l != 0 && i.t++ > -1)
			i.l = 0;	
	}
	s1[i.t] = NULL;
	return (s1);
}

int	double_pointer_nbr(char *s, char c)
{
	t_index i;

	i = initialize_index();
	while (s[i.i])
	{
		while ((s[i.i] && (((s[i.i] != c && s[i.i] != '|' && s[i.i] != '>' && s[i.i] != '<')) || is_in_quote(s, i.i))))
		{
			if (i.k++ == 0)
				i.count++;
			i.i++;
		}
		i.k = 0;
		while (s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|')
		{
			if (i.k++ == 0)
				i.count++;
			i.i++;
		}
		i.k = 0;
		while (s[i.i] && s[i.i] == c)
			i.i++;
	}
	return (i.count);
}


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

int simple_pointer_nbr(char *s, char c, char **s1, t_m *var)
{
	t_index i;

	i = initialize_index();
	i.t = -1;
	while (s[i.i] && s[i.i] != '\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		while ((s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|') && i.count++ > -1)
			i.i++;	
		if (i.count != 0 && i.t++ > -2)
		{	
			if (malloc_simple_pointer(i.count, i.t, s1, var) == 2)
				return (2);
			i.count = 0;			
		}
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || is_in_quote(s, i.i)) && i.count++ > -1)
			i.i++;
		if (i.count != 0 && i.t++ > -2)
		{
			if (malloc_simple_pointer(i.count, i.t, s1, var) == 2)
				return (2);
			i.count = 0;
		}
	}
	return (0);
}

int	get_args(char ***args, char *s, char c, t_m *var)
{	
	if (!s)
		return (2);
	*args = (char **)ft_calloc((double_pointer_nbr(s, c) + 1), sizeof(char *));
	if (!*args)
	{
		free(var->args_line);
		free_doubletab(var->env);
		write(2, "malloc error\n", 13);
		return (2);
	}
	if (simple_pointer_nbr(s, c, *args, var) == 2)
		return (2);
	fill_args(s, ' ', *args);
	return (1);
}
