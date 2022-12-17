/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:29:26 by chillion          #+#    #+#             */
/*   Updated: 2022/12/17 15:06:13 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	ft_init_heredoc(t_m *var)
{
	pid_t	pid;

	var->h_status = open(".heredocstatus", O_RDWR | O_CREAT, 0644);
	close(var->h_status);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	(pid) = fork();
	if ((pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((pid) == 0)
	{
		if (ft_strcmplen(var->redir, "<<") > 0)
			handle_heredoc_child(var);
		if (g_exit_status != -42)
			unlink(".heredocstatus");
		return (free_child_heredoc(var), exit(1));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, 0, 0);
		g_exit_status = 130;
		var->h_status = open(".heredocstatus", O_RDWR);
		ft_signal(1);
	}
}

void	ft_daddy(t_m *var, int *pid, int nbcmd)
{
	int	i;

	i = 0;
	ft_signal(2);
	while (i < nbcmd && nbcmd != 0 && var->h_status == -1)
	{
		if (is_env_builtin(var->cmd[0]) && var->tablen == 1)
			break ;
		waitpid(pid[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		i++;
	}
	ft_signal(1);
	if (var->h_status > 2)
	{
		close(var->h_status);
		var->h_status = 0;
		unlink(".heredocstatus");
	}
}

int	ft_exec(t_m *var, char ***args)
{
	var->exec = 0;
	var->tabexec = 0;
	var->h_status = -1;
	if (!args)
		return (0);
	var->pid = (int *)malloc(sizeof(int) * (var->tablen + 1));
	if (!var->pid)
		return (free_parent(var), 1);
	var->pid[var->tablen] = 0;
	if (ft_strcmplen(var->redir, "<<") > 0)
		ft_init_heredoc(var);
	ft_init_all_pipe(var);
	if (var->tablen >= 1 && var->h_status == -1)
	{
		while ((var->exec) < var->tablen)
		{
			ft_do_pipe_fork(var, args[var->exec][0], \
			args[var->exec], &var->pid[var->exec]);
			var->exec++;
		}
	}
	if (var->h_status != -1)
		ft_unlink_all(var, 0);
	ft_daddy(var, var->pid, var->tablen);
	return (0);
}

void	ft_check_args(int argc)
{
	if (argc > 1)
	{
		write(2, "Invalid number of arguments\n", 29);
		exit(1);
	}
	if (!isatty(0))
	{
		write(2, "Error invalid STDIN\n", 21);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;

	ft_check_args(argc);
	ft_signal(1);
	initialize_var(&var);
	if (ft_create_env(&var, envp) == -1)
		return (ft_printf("Error : Malloc for keep env fail\n"), 1);
	while (1)
	{
		var.args_line = NULL;
		ft_init_commands_history(&var);
		if (!will_return_nothing(var.args_line) && \
		is_cmdline_valid(var.args_line, argc, argv))
		{
			var.args_line = new_env_var(var.args_line, var.env);
			ft_parsing(&var, var.env, &var.cmd, &var.redir);
			if ((empty(var.cmd, &var) + empty(var.redir, &var)) > 0)
				do_exec(&var);
			else
				free_parsing(&var);
		}
		free(var.args_line);
	}
	return (0);
}
