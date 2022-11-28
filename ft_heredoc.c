/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:47 by chillion          #+#    #+#             */
/*   Updated: 2022/11/28 19:20:43 by chillion         ###   ########.fr       */
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
		write((*var).fd1, str, (ft_strlen(str) - k));
		close((*var).fd1);
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
	char	*buffer;
	char	*str;

	buffer = (char *)malloc(sizeof(char) * 2);
	if (!buffer)
		return ;
	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return ;
	write_first_c(buffer, str);
	write(1, ">", 1);
	while (n > 0)
	{
		n = (read(0, buffer, 1));
		if (n == -1)
			ft_cleanheredoc_fd(str, buffer, (*var).comp, (*var).fd1);
		buffer[1] = '\0';
		str = ft_strjoin_free(str, buffer);
		if (!ft_eof_find(str, (*var).comp, j, var))
			break ;
		ft_write_here_sign(buffer[0]);
		j++;
	}
	return (ft_cleanheredoc_fd(str, buffer, (*var).comp, (*var).fd1));
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
		ft_trunc_init_fd(".tmpheredoc", &(*var).fd1);
		ft_heredoc_fd(var, n, j);
	}
}
