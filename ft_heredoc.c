/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:47 by chillion          #+#    #+#             */
/*   Updated: 2022/12/02 12:32:31 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_eof_find(char *str, char *comp, int i, t_m *var)
{
	int	j;
	int	k;

	k = ft_strlen(comp);
	if (i < k)
		return (1);
	j = ft_strncmp((str + (i - k)), comp, k);
	if (j == 0 && (i == k || str[i - k - 1] == '\n'))
	{
		write((*var).fdin, str, (ft_strlen(str) - k));
		close((*var).fdin);
		return (0);
	}
	return (1);
}

void	ft_write_here_sign(char c)
{
	if (c == '\n')
	{
		write(1, ">", 1);
	}
}

void	write_first_c(char *buffer, char *str)
{
	buffer[0] = '\0';
	str[0] = '\0';
}

void	ft_heredoc_fd(t_m *var, int n, int j)
{
	char	*str;

	// signal(SIGINT, SIG_DFL);
	signal(SIGINT, handle_sigint_2);
	signal(SIGQUIT, SIG_IGN);
	while (n > 0)
	{
		str = readline(">");
		if (!str)
		{
			write(2, "warning: don't find end-of-file (wanted `", 42);
			ft_putstr_fd((*var).comp, 2);
			write(2, "')\n", 4);
			return ;
		}
		if (ft_strcmp((*var).comp, str) == 0)
			break ;
		write((*var).fdin, str, ft_strlen(str));
		write((*var).fdin, "\n", 2);
		free(str);
		j++;
	}
	free (str);
	return (ft_cleanheredoc_fd(NULL, NULL, (*var).comp, (*var).fdin));
}

void	ft_check_heredoc(char *argv, char *stop, t_m *var)
{
	int	n;
	int	j;

	n = 1;
	j = 1;
	(*var).heredoc_status = 0;
	if (!ft_strncmp(argv, "<<", ft_strlen(argv)))
	{
		(*var).comp = ft_strjoin(stop, "\n");
		(*var).heredoc_status = 1;
		ft_trunc_init_fd(".tmpheredoc", &(*var).fdin);
		ft_heredoc_fd(var, n, j);
	}
}
