/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:17:00 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 16:24:41 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialize_var(t_m *var)
{
    var->args_line = NULL;
	var->env = NULL;
	var->h_fd = 0;
	var->pcmd_line = 0;
	var->split_path = NULL;
	var->path = NULL;
	var->arg = NULL;
	var->pipex = NULL;
	var->exec = 0;
	var->tabexec = 0;
	var->tablen = 0;
	var->comp = NULL;
	var->heredoc_status = 0; 
	var->cmd = NULL;
	var->redir = NULL;
	var->fdin = 0;
	var->fdout = 0;
	var->cmdtype = 0;
	var->heredoc = NULL;
	var->status = 0;
	var->pid = NULL;
	var->h_status = 0;
	var->fd_status_in = 0; 
	var->fd_status_out = 0;
	var->line = 0;
}