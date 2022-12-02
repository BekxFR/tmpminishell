/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:30:58 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 16:29:16 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_double_pointer_cmd(char ***tab, int count, char **args, t_m *var)
{
	*tab = ft_calloc(sizeof(char *), (count + 1));
	if (!tab)
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_doubletab(args);
		free_error_tripletab(tab, count);
		return (2);
	}
	return (0);
}

int	malloc_cmd(char ***cmd, char **args, t_m *var)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>') && i.i++ > -1)
			i.counter++;
		if (args[i.i] && args[i.i][0] == '|')
		{		
			if (malloc_double_pointer_cmd(&cmd[i.j], i.counter, args, var) == 2)
				return (2);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
			i.i = i.i + 2;
	}
	if (malloc_double_pointer_cmd(&cmd[i.j], i.counter, args, var) == 2)
		return (2);	
	return (0);
}