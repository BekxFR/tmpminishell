/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 16:05:21 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_m *var, char **envp, char ****cmd, char ****redir)
{

	char	**args;

	if (!var->args_line || var->args_line[0] == '\n')
		return (0);
	if (is_cmdline_valid(var->args_line) == 2)
		return (2);
	if (get_args(&args, var->args_line, ' ', var) == 2)
		return (2);
	args = get_env_var(args, envp);
	*cmd = NULL;
	*redir = NULL;
	if (set_in_cmd(args, var) == 2)
		return (2);
	*cmd = clean_args(*cmd);
	*redir = clean_args(*redir);
	return (0);
}