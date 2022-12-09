/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlink.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:38:45 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 19:37:06 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(char ***redir, int i)
{
	int	j;

	j = 0;
	while (redir[i][j])
	{
		if (ft_strncmp(redir[i][j], ".heredoc", 5) == 0){
			unlink(redir[i][j]);}
		j++;
	}
}

void	ft_unlink_all(t_m *var, int i)
{
	int	j;

	j = 0;
	if (ft_strcmplen(var->redir, "<<") > 0)
		handle_heredoc(var);
	while(var->redir[i])
	{
		while (var->redir[i][j])
		{
			if (ft_strncmp(var->redir[i][j], ".heredoc", 5) == 0){
				unlink(var->redir[i][j]);}
			j++;
		}
		i++;
	}
}
