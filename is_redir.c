/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:24:42 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 14:11:56 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_out(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], ">>") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_redir(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (strcmp(redir[i], "<<") == 0)
			return (1);
		if (strcmp(redir[i], "<") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">>") == 0)
			return (1);
		if (ft_strcmp(redir[i], ">") == 0)
			return (1);
		i++;
	}
	return (0);
}
