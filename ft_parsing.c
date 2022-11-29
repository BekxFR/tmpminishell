/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/29 11:36:30 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(char *s, char **envp, char ****cmd, char ****redir)
{
	// char	***cmd;
	// char	***redir;
	char	**args;

	if (!s || s[0] == '\n')
		return ;
	if (!is_cmdline_valid(s))
		return ;
	args = get_args(s, ' ');
	if (!args)
		return ;	
	args = get_env_var(args, envp);
	*cmd = NULL;
	*redir = NULL;
	set_in_cmd(&*cmd, &*redir, args, s);
	if (!*cmd)
		return;
	*cmd = clean_args(*cmd);
	*redir = clean_args(*redir);
}