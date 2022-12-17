/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:10:50 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/17 14:30:45 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsing(t_m *var)
{
	free_tripletab(var->redir);
	free_tripletab(var->cmd);
}

int	empty(char ***tab, t_m *var)
{
	t_index	i;

	(void)var;
	i = initialize_index();
	while ((tab[i.i] && tab[i.i][0]) || ft_puttriplelentab(tab) > i.i)
	{	
		i.j = 0;
		while ((tab[i.i] && tab[i.i][i.j] && tab[i.i][i.j][0]) \
		|| ft_tablen(tab[i.i]) > i.j)
		{
			if (tab[i.i][i.j][0])
				i.k++;
			i.j++;
		}
		if (tab[i.i])
		i.i++;
	}
	return (i.k);
}

void	do_exec(t_m *var)
{
	var->tablen = ft_puttriplelentab(var->cmd);
	ft_exec(var, var->cmd);
	update_last_env(var);
	free_parent(var);
}

void	no_args_line(t_m *var)
{
	free_doubletab(var->env);
	rl_clear_history();
	write(2, "exit\n", 6);
}
