/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:38:18 by chillion          #+#    #+#             */
/*   Updated: 2022/12/13 12:37:06 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_fd_status(char *file, int *fd)
{
	*fd = open(file, O_RDWR);
	if (*fd == -1 && ((errno == EACCES) || (errno == EISDIR)))
	{
		ft_putstr_fd(file, 2);
		perror(" ");
		return (-1);
	}
	if (*fd != -1)
		close (*fd);
	return (0);
}

int	ft_append_init_fd(char *file, int *fd)
{
	(*fd) = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd(file, 2);
		perror(" ");
		return (-1);
	}
	return (0);
}

int	ft_trunc_init_fd(char *file, int *fd)
{
	(*fd) = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd(file, 2);
		perror(" ");
		return (-1);
	}
	return (*fd);
}
