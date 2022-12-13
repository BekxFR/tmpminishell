/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:07:01 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 13:04:58 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, handle_sigint_1);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		signal(SIGINT, handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 3)
	{
		signal(SIGINT, handle_sigint_3);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 4)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 5)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	handle_sigint_1(int sig)
{
	g_exit_status += sig;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigint_2(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigint_3(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		write(1, "\n", 2);
		signal(SIGINT, SIG_IGN);
		g_exit_status = -42;
		close(0);
	}
}
