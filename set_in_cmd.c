/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/29 15:47:00 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_triple_pointer_len(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '|' && !is_in_quote(s, i))
		{
			count++;
			i = i + 2;
		}
		i++;
	}
	count = count + 1;
	// printf("count : %i\n", count);
	return (count);
}

char	**malloc_double_pointer(char **tab, int count, char **args)
{
	tab = ft_calloc(sizeof(char *), (count + 1));
	if (!tab)
	{
		free_doubletab(args);
		free_error_tripletab(&tab, count);
		exit (-1);
	}
	// printf("c3\n");
	return (tab);
}

char	***malloc_redir(char ***redir, char **args)
{
	t_index	i;

	i = initialize_index();
	// printf("c3zero i : %i\n", i.i);
	while (args[i.i])
	{
		while (args[i.i] && args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>')
		{
			// printf("c3 i : %i\n", i.i);
			i.i++;
		}
		// printf("c3uno i : %i\n", i.i);
		if (args[i.i] && args[i.i][0] == '|')
		{		
			// printf("c3unobis : i.counter : %i\n", i.counter);
			redir[i.j] = malloc_double_pointer(redir[i.j], i.counter, args);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
		{
			i.i = i.i + 2;
			i.counter = i.counter + 2;
		}
	}
	// printf("c3unobis : i.counter end: %i\n", i.counter);
	redir[i.j] = malloc_double_pointer(redir[i.j], i.counter, args);		
	return (redir);
}

char	***malloc_cmd(char ***cmd, char **args)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>') && i.i++ > -1)
			i.counter++;
		// printf("c2 i : %i\n", i.i);
		if (args[i.i] && args[i.i][0] == '|')
		{		
			// printf("c2unobis : i.counter : %i\n", i.counter);
			cmd[i.j] = malloc_double_pointer(cmd[i.j], i.counter, args);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
			i.i = i.i + 2;
	}
	// printf("c3unobis : i.counter end: %i\n", i.counter);
	cmd[i.j] = malloc_double_pointer(cmd[i.j], i.counter, args);	
	return (cmd);
}

char	***fill_cmd(char ***cmd, char **args, char ***redir)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		// printf("c1\n");	
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>'))
		{	
			// printf("c1bis : args[i.i] : %s\n", args[i.i]);
			// printf("j : %i, k : %i, i : %i\n", i.j, i.k, i.i);
			cmd[i.j][i.k] = args[i.i];
			i.k++;
			i.i++;
		}
		// printf("c1terbis\n");
		if (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
		{
			// printf("c1terter\n");
			redir[i.i1][i.i2++] = args[i.i++];
			redir[i.i1][i.i2++] = args[i.i++];
			// i.i = i.i + 2;
		}
		if (args[i.i] && args[i.i][0] == '|' && i.i++ > -1)
		{
			// printf("c1ter\n");
			i.k = 0;
			i.j++;
			i.i1++;
			i.i2 = 0;
		}
		// printf("c1quater\n");
	}
	// printf("c1cinquies\n");

	free(args);
	return (cmd);
}

void	set_in_cmd(char ****cmd, char ****redir, char **args, char *s)
{	
	int		triple_pointer_len;

	triple_pointer_len = ft_triple_pointer_len(s);
	// printf("triple pointer len : %i\n", triple_pointer_len);
	*cmd = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!*cmd)
	{
		free_doubletab(args);
		exit (-1);
	}
	*redir = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!*redir)
	{
		free_tripletab(*cmd);
		free_doubletab(args);
		exit (-1);
	}
	// printf("c1\n");
	*cmd = malloc_cmd(*cmd, args);
	*redir = malloc_redir(*redir, args);
	*cmd = fill_cmd(*cmd, args, *redir);
	// return (cmd);
}
