/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:28:56 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 18:43:32 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_last_env(t_m *var)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!var->cmd || !var->cmd[i] || !var->cmd[i][j])
    {
        return (0);
    }
	while (var->cmd[i])
	{
		j = 0;
		while (var->cmd[i][j])
			j++;
		i++;
	}
	export_env("_=", var->cmd[i - 1][j - 1], var);
	return (1);
}
