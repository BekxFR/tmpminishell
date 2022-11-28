/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:41:21 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 15:18:50 by mgruson          ###   ########.fr       */
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


char *malloc_simple_pointer(int count, int t, char **s1)
{
	s1[t] = (char *)ft_calloc((count + 1), sizeof(char));
	if (!s1[t])
	{
		free_error_doubletab(s1, t);
		exit (-1);
	}
	// printf("c1\n");
	return (s1[t]);
}

char	**simple_pointer_nbr(char *s, char c, char **s1)
{
	t_index i;

	i = initialize_index();
	while (s[i.i] && s[i.i] != '\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		while ((s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|') && i.count++ > -1)
			i.i++;	
		if (i.count != 0)
		{	
			s1[i.t] = malloc_simple_pointer(i.count, i.t, s1);
			i.t++;
			i.count = 0;			
		}
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || is_in_quote(s, i.i)) && i.count++ > -1)
			i.i++;
		if (i.count != 0)
		{
			s1[i.t] = malloc_simple_pointer(i.count, i.t, s1);
			i.t++;
			i.count = 0;
		}
	}
	return (s1);
}

char **get_args(char *s, char c)
{
	char	**args;
	
	if (!s)
		return (NULL);
	args = NULL;
	args = (char **)ft_calloc((double_pointer_nbr(s, c) + 1), sizeof(char *));
	if (!args)
		exit (-1);
	// free(args);
	// return (NULL);
	args = simple_pointer_nbr(s, c, args);
	if (!*args)
	{
		return (args);
	}
	args = fill_args(s, ' ', args);
	return (args);
}
