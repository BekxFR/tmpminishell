/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:37:23 by chillion          #+#    #+#             */
/*   Updated: 2022/12/13 12:45:18 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pipe(t_m *var, int i)
{
	var->pipex[i] = (int *)malloc(sizeof(int) * (2));
	if (!var->pipex[i])
		return (2);
	if (pipe(var->pipex[i]) == -1)
		return (write(2, "Error with pipe\n", 17), ft_fork_fail(var), 2);
	return (0);
}

int	ft_init_all_pipe(t_m *var)
{
	int	i;

	i = 0;
	var->pipex = (int **)malloc(sizeof(int *) * (var->tablen + 1));
	if (!var->pipex)
		return (printf("malloc error\n"), 2);
	var->pipex[var->tablen] = NULL;
	while (i < var->tablen)
	{
		if (ft_init_pipe(var, i) == 2)
			return (2);
		i++;
	}
	return (0);
}
