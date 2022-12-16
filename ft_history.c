/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:39:09 by chillion          #+#    #+#             */
/*   Updated: 2022/12/16 13:28:36 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history_init_fd(char *file, int *fd)
{
	int	t;

	(void)t;
	(*fd) = open(file, O_RDONLY | O_RDWR | O_APPEND);
	if (*fd == -1)
	{
		t = unlink(file);
		(*fd) = open(file, O_RDONLY | O_RDWR | O_CREAT, 0644);
	}
}

void	ft_init_commands_history(t_m *var)
{
	char	*str;

	str = NULL;
	while (1)
	{
		ft_signal(1);
		str = readline("minishell>");
		if (!str)
			break ;
		else if (ft_strlen(str))
		{
			add_history(str);
			ft_history_init_fd(".history", &(*var).h_fd);
			write((*var).h_fd, str, ft_strlen(str));
			write((*var).h_fd, "\n", 1);
			close((*var).h_fd);
			(*var).args_line = ft_strdup(str);
			free(str);
			str = NULL;
			break ;
		}
	}
}
