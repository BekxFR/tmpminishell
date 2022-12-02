/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:46:03 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 18:09:08 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_heredoc(t_m *var)
{
	int	heredoc_len;

	heredoc_len = ft_strcmplen(var->redir, "<<");
	var->heredoc = ft_calloc(sizeof(char *), (heredoc_len + 1));
	return (var->heredoc);
}

char	**get_heredoc_filename(char **heredoc, int i)
{
	char	*str;

	str = ft_strjoin(".heredoc", ft_itoa(i));
	heredoc[i] = ft_calloc(sizeof(char), \
	(ft_strlenint(str) + ft_intlen(i) + 1));
	ft_strlcpy(heredoc[i], str, (ft_strlenint(str) + 1));
	return (heredoc);
}

void	get_heredoc(char *str, t_m *var)
{
	static int	i = 0;

	(*var).comp = ft_strdup(str);
	var->heredoc = get_heredoc_filename(var->heredoc, i);
	(*var).heredoc_status = 1;
	ft_trunc_init_fd(var->heredoc[i], &(*var).fdin);
	ft_heredoc_fd(var, 1, 1);
	close((*var).fdin);
	i++;
}

void	 handle_heredoc(t_m *var)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	var->heredoc = malloc_heredoc(var);
	while (var->redir[i])
	{
		j = 0;
		while (var->redir[i][j])
		{
			if (strcmp(var->redir[i][j], "<<") == 0)
			{
				get_heredoc(var->redir[i][j + 1], var);
				var->redir[i][j][1] = '\0';
				free(var->redir[i][j + 1]);
				var->redir[i][j + 1] = NULL;
				var->redir[i][j + 1] = var->heredoc[k];
				k++;
			}
			j++;
		}
		i++;
	}
}
