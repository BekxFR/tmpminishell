/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/28 18:26:42 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ft_parsing(char *s, char **envp)
{
	char	***cmd;
	char	***redir;
	char	**args;

	if (!s || s[0] == '\n')
		return (NULL);
	if (!is_cmdline_valid(s))
		return (NULL);
	args = get_args(s, ' ');
	if (!args)
		return (NULL);	
	args = get_env_var(args, envp);
	cmd = NULL;
	set_in_cmd(&cmd, &redir, args, s);
	if (!cmd)
		return(NULL);
	cmd = clean_args(cmd);
	redir = clean_args(redir);
	ft_puttripletab(cmd);
	printf("\n-----\n");
	ft_puttripletab(redir);
	return (cmd);
}