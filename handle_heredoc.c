/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:46:03 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 13:48:24 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_heredoc(t_m *var)
{
	int	heredoc_len;

	heredoc_len = ft_strcmplen(var->redir, "<<");
	var->heredoc = ft_calloc(sizeof(char *), (heredoc_len + 1));
	if (!var->heredoc)
	{
		free_all(var);
		return (NULL);
	}
	return (var->heredoc);
}

char	*get_heredoc(t_m *var, int k)
{
	static int	i = 0;
	char		*str;
	char		*itoa;

	(*var).heredoc_status = 1;
	itoa = ft_itoa(k);
	str = ft_strjoin(".heredoc", itoa);
	free(itoa);
	//ft_trunc_init_fd(str, &(*var).fdin);
	// ft_heredoc_fd(var, 1);
	//close((*var).fdin);
	i++;
	return (str);
}

int	handle_heredoc(t_m *var)
{
	t_index		i;
	static int	k = 0;

	i = initialize_index();
	malloc_heredoc(var);
	if (!var->heredoc)
		return (2);
	while (var->redir[i.i])
	{
		i.j = -1;
		while (var->redir[i.i][++i.j])
		{
			if (strcmp(var->redir[i.i][i.j], "<<") == 0)
			{
				var->redir[i.i][i.j][1] = '\0';
				(*var).comp = ft_strdup(var->redir[i.i][i.j + 1]);
				free(var->redir[i.i][i.j + 1]);
				var->redir[i.i][i.j + 1] = get_heredoc(var, k);
				k++;
			}
		}
		i.i++;
	}
	free(var->heredoc);
	return (0);
}

/* ----- */

char	*get_heredoc_child(t_m *var, int k)
{
	static int	i = 0;
	char		*str;
	char		*itoa;

	(*var).heredoc_status = 1;
	itoa = ft_itoa(k);
	str = ft_strjoin(".heredoc", itoa);
	free(itoa);
	ft_trunc_init_fd(str, &(*var).fdin);
	ft_heredoc_fd(var, 1);
	close((*var).fdin);
	i++;
	return (str);
}

int	handle_heredoc_child(t_m *var)
{
	t_index		i;
	static int	k = 0;

	i = initialize_index();
	malloc_heredoc(var);
	if (!var->heredoc)
		return (2);
	while (var->redir[i.i])
	{
		i.j = -1;
		while (var->redir[i.i][++i.j])
		{
			if (strcmp(var->redir[i.i][i.j], "<<") == 0)
			{
				var->redir[i.i][i.j][1] = '\0';
				(*var).comp = ft_strdup(var->redir[i.i][i.j + 1]);
				free(var->redir[i.i][i.j + 1]);
				var->redir[i.i][i.j + 1] = get_heredoc_child(var, k);
				k++;
			}
		}
		i.i++;
	}
	free(var->heredoc);
	return (0);
}

