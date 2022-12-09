/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 17:52:01 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int will_return_nothing(char * str)
{
	int i;

	i = 0;
	if (str[i] == '\n' && ft_strlen(str) == 0)
		return (1);
	if ((str[i] == ':' || str[i] == '!') && ft_strlen(str) == 1)
		return (1);
	while (str[i] != 0 && str[i] != '\n')
	{
		if (str[i] != ' ')
			return (0);	
		i++;
	}
	return (1);
}

int	ft_parsing(t_m *var, char **envp, char ****cmd, char ****redir)
{
	char	**args;

	if (!var->args_line || will_return_nothing(var->args_line))
	{
		return (0);
	}
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
