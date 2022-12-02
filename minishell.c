

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

// void	write_first_c(char *buffer, char *str)
// {
// 	buffer[0] = '\0';
// 	str[0] = '\0';
// }

void	ft_init_commands_history(t_m *var)
{
	char *str;

	while (1)
	{
		if (str)
			free(str);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
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
			break ;
		}
		else if (!ft_strlen(str))
		{
			if (*str)
				free(str);
		}
	}
}

void	ft_print_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("SPLIT[%d]=%s]\n", i, str[i]);
		i++;
	}
	ft_printf("-----------------\n");
}

void	handle_sigint_2(int sig)
{
	int status = 0;

	(void)status;
	status += sig;
	if (sig == 2)
	{
		status = 130;
		printf("\n");
		// rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_daddy(t_m *var, int *pid, int nbcmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	(void)var;
	signal(SIGINT, handle_sigint_2);
	signal(SIGQUIT, SIG_IGN);
	write(2, "ZZZZZZZZZ\n", 11);
	while (i < nbcmd && nbcmd != 0)
	{
		printf("pid=%d\n", pid[i]);
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	write(2, "TESTEURER\n", 11);
	free(pid);
}

int	ft_exec(t_m *var, char ***args)
{
	int	*pid;

	var->exec = 0;
	var->tabexec = 0;
	pid = (int *)malloc(sizeof(int) * (var->tablen + 1));
	if (!pid)
		return (printf("malloc error\n"), 1);
	pid[var->tablen] = 0;
	if (var->tablen == 1)
		ft_do_fork(var, args[0][0], args[0], &pid[0]);
	else if (var->tablen > 1)
	{
		while ((var->exec) < var->tablen)
		{
			ft_do_pipe_fork(var, args[var->exec][0], args[var->exec], &pid[var->exec]);
			var->exec++;
		}
	}
	return (ft_daddy(var, pid, var->tablen), 0);
}

int	ft_puttriplelen(char ***test, t_m *var)
{
	var->tablen = 0;

	if (!test)
		return (var->tablen);
	while(test[var->tablen])
		var->tablen++;
	return (var->tablen);
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;

	signal(SIGINT, handle_sigint); /* ctrl + c  affiche un nouveau prompt */
	signal(SIGQUIT, SIG_IGN); /* ctrl + \  ne fait rien */
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_printf("Error : Wrong Number of arguments\n"), 1);
	if (ft_env(&var, envp) == -1)
		return (ft_printf("Error : Malloc for keep env fail\n"), 1);
	while (1)
	{
		var.args_line = NULL;
		ft_init_commands_history(&var);
		if (!var.args_line)
			return (ft_free_split(var.env) , printf("exit\n"), 0);
		ft_printf("Command is :%s\n", var.args_line);
		if (ft_parsing(&var, envp, &var.cmd, &var.redir) == 2)
			return (2);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
		ft_puttriplelen(var.cmd, &var);
		ft_exec(&var, var.cmd);
		free_tripletab(var.cmd);
		free_tripletab(var.redir);
		free(var.args_line);
	}
	return (0);
}
