/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmdline_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:19 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 17:04:39 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_handled_special_char(char *str, int i)
{	
	int	inf;
	int	sup;
	int	bar;
	int	space;

	inf = 0;
	sup = 0;
	bar = 0;
	space = 0;
	while ((str[i] == '|' || (str[i] == ' ' && (inf > 0 || sup > 0 || bar > 0)) \
	|| str[i] == '>' || str[i] == '<' ) && !is_in_quote(str, i))
	{
		if (str[i] == '|' && i++ > -1 && bar++ > -1 && \
		((bar > 1 || sup > 0 || inf > 0)))
			return (printf("syntax error near unexpected token `|'\n"), 2);
		if ((str[i] == '>' && i++ > -1 && sup++ > -1) \
		&& (sup > 2 || space > 0 || bar > 0 || inf > 0))
			return (printf("syntax error near unexpected token `>'\n"), 2);
		if (str[i] == '<' && i++ > -1 && inf++ > -1 && \
		(inf > 2 || space > 0 || sup > 0 || bar > 0))
			return (printf("syntax error near unexpected token `<'\n"), 2);
		while (str[i] == ' ' && i++ > -1)
			space++;
	}
	return (1);
}

int	are_handled_syntax_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_handled_special_char(str, i) == 2)
			return (2);
		i++;
	}
	return (1);
}

int	are_pipe_and_redir_correct(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (printf("syntax error near unexpected token `|'\n"), 2);
	while (str[len] == ' ')
		len--;
	if (str[len] == '|' || str[len] == '<' || str[len] == '>')
		return (printf("syntax error near unexpected token `newline'\n"), 2);
	return (1);
}

int	is_cmdline_valid(char *str)
{	
	if (are_handled_syntax_error(str) == 2)
		return (2);
	if (are_pipe_and_redir_correct(str) == 2)
		return (2);
	return (1);
}

/* Dans int are_handled_syntax_error(char *str), 
rajouter entre while(str[i]) et 
if (is_handled_special_char(str, i) == 2) 
pour ne pas gerer des parenthese ouvertes :

		// if (str[i] == 34)
		// {
		// 	i++;
		// 	while (str[i] && str[i] != 34)
		// 		i++;
		// 	if (str[i] == 0)
		// 		return(printf("syntax error double quote unclosed\n"), 2);
		// }
		// if (str[i] == 39)
		// {
		// 	i++;
		// 	while (str[i] && str[i] != 39)	
		// 		i++;
		// 	if (str[i] == 0)
		// 		return(printf("syntax error simple quote unclosed\n"), 2);
		// }
		
*/