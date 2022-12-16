/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/15 14:00:39 by mgruson          ###   ########.fr       */
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
	return (count);
}

char	***fill_cmd(char ***cmd, char **args, char ***redir)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && \
		args[i.i][0] != '<' && args[i.i][0] != '>'))
			cmd[i.j][i.k++] = args[i.i++];
		if (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
		{
			redir[i.i1][i.i2++] = args[i.i++];
			redir[i.i1][i.i2++] = args[i.i++];
		}
		if (args[i.i] && args[i.i][0] == '|' && i.i++ > -1)
		{
			i.k = 0;
			i.j++;
			i.i1++;
			i.i2 = 0;
			free(args[i.i - 1]);
		}
	}
	return (cmd);
}

int	set_in_cmd(char **args, t_m *var)
{	
	int		triple_pointer_len;

	triple_pointer_len = ft_triple_pointer_len(var->args_line);
	var->cmd = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!var->cmd)
	{
		free(var->args_line);
		free_doubletab(args);
		return (2);
	}
	var->redir = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!var->redir)
	{
		free(var->args_line);
		free_tripletab(var->cmd);
		free_doubletab(args);
		return (2);
	}
	if (malloc_cmd(var->cmd, args, var) == 2)
		return (2);
	if (malloc_redir(var->redir, args, var) == 2)
		return (2);
	var->cmd = fill_cmd(var->cmd, args, var->redir);
	return (0);
}
