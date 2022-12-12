/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:31:07 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 11:43:28 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_double_pointer_redir(char ***tab, int count, char **args, t_m *var)
{
	*tab = ft_calloc(sizeof(char *), (count + 1));
	if (!*tab)
	{
		free(var->args_line);
		free_doubletab(args);
		free_tripletab(var->cmd);
		free_error_tripletab(tab, count);
		return (2);
	}
	return (0);
}

int	malloc_redir(char ***redir, char **args, t_m *var)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && args[i.i][0] != '|' \
		&& args[i.i][0] != '<' && args[i.i][0] != '>')
			i.i++;
		if (args[i.i] && args[i.i][0] == '|')
		{		
			if (malloc_double_pointer_redir(&redir[i.j], i.counter, args, var))
				return (2);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>') \
		&& i.i++ > -1 && i.i++ > -1)
			i.counter = i.counter + 2;
	}
	if (malloc_double_pointer_redir(&redir[i.j], i.counter, args, var) == 2)
		return (2);
	return (0);
}
