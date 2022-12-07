/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_std_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/07 11:18:58 by chillion         ###   ########.fr       */
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

void	out(char *redir_file, char c, t_m *var)
{
	if (var->fdout != 1)
		close(var->fdout);
	if (c == 'S')
	{
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (var->fdout == -1)
			return ;
			
	}
	if (c == 'D')
	{
		var->fdout = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (var->fdout == -1)
			return ;
	}
}

void	in(char *redir_file, char c, t_m *var)
{
	if (var->fdin != 0)
		close(var->fdin);
	if (c == 'S')
	{
		var->fdin = open(redir_file, O_RDONLY, 0777);
		if (var->fdin == -1)
		{
			write(2, "ERROR\n", 6);
			exit (-2);
		}
		// close(fd);
	}
}

void	ft_fd_init(t_m *var)
{
	if (var->fdin == 0)
	{
		if((var->exec + 1) != (var->tablen))
			var->fdin = var->pipex[0][0];
	}
	if (var->fdout == 1)
	{
		if((var->exec + 1) != (var->tablen))
			var->fdout = var->pipex[0][1];
	}
}

// void	ft_fd_init(t_m *var)
// {
// 	ft_printf("var->fdin=%d\n", var->fdin);
// 	ft_printf("var->fdout=%d\n", var->fdout);
// 	if (var->fdin == 0)
// 	{
// 		write(2, "redirect FD1 to pipe0\n", 23);
// 		if((var->exec + 1) != (var->tablen))
// 		{
// 			var->fdin = var->pipex[0];
// 			ft_printf("var->fdin=%d\n", var->fdin);
// 		}
// 	}
// 	if (var->fdout == 1){
// 		write(2, "redirect FD2 to pipe1\n", 23);
// 		var->fdout = var->pipex[1];
// 		// if((var->exec + 1) != (var->tablen))
// 		// {
// 		// 	ft_printf("var->fdout=%d\n", var->fdout);
// 		// 	write(2, "ADDredirect FD2 to pipe1\n", 26);
// 		// }
// 	}
// }

void	get_std_redir(char **redir, t_m *var)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<") == 0){
			write(2, "FIND < \n", 9);
			in(redir[i + 1], 'S', var);}
		if (ft_strcmp(redir[i], ">>") == 0){
			write(2, "FIND >> \n", 10);
			out(redir[i + 1], 'D', var);}
		if (ft_strcmp(redir[i], ">") == 0){
			write(2, "FIND > \n", 9);
			out(redir[i + 1], 'S', var);}
		i = i + 2;
	}
	// ft_fd_init(var);
}
