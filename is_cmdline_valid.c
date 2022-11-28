/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmdline_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:19 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 19:49:18 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_handled_special_char(char *str, int i)
{	
	int inf;
	int sup;
	int bar;
	int space;
	
	inf = 0;
	sup = 0;
	bar = 0;
	space = 0;
	while((str[i] == '|' || (str[i] == ' ' && (inf > 0 || sup > 0 || bar > 0))\
	|| str[i] == '>' || str[i] == '<' ) && !is_in_quote(str, i))
	{
		if (str[i] == '|' && i++ > -1 && bar++ > -1\
		&& ((bar > 1 || sup > 0 || inf > 0)))
				return (0);
		if ((str[i] == '>' && i++ > -1 && sup++ > -1)\
		&& (sup > 2 || space > 0 || bar > 0 || inf > 0)) 
				return (0);
		if (str[i] == '<' && i++ > -1 && inf++ > -1 &&\
		(inf > 2 || space > 0 || sup > 0 || bar > 0))
				return (0);
		while (str[i] == ' ' && i++ > -1)
			space++;
	}
	return (1);
}
		
int are_handled_special_char(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == 33)
		{
			i++;
			while (str[i] && str[i] != 33)
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the double quote\n", 31);
				return (0);
			}
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)	
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the simple quote\n", 31);
				return (0);
			}
		}
		if (!is_handled_special_char(str, i))
		{
			write(1, "Error : there are non handled special character\n", 48);
			return (0);	
		}
		i++;
	}
	return (1);	
}

int quote_are_closed(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the double quote\n", 31);
				return (0);
			}
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)	
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the simple quote\n", 31);
				return (0);
			}
		}
		if (!is_handled_special_char(str, i))
		{
			write(1, "Error : there are non handled special character\n", 48);
			return (0);	
		}
		i++;
	}
	return (1);	
}

int	are_pipe_and_redir_correct(char *str)
{
	int i;
	int len; 
	
	i = 0;
	len = ft_strlen(str) - 1;
	while(str[i] == ' ')
		i++;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')	
		return (write(1, "wrong start string\n", 19), 0);
	while(str[len] == ' ')
		len--;
	if (str[len] == '|' || str[len] == '|' || str[len] == '|')
		return (write(1, "wrong end string\n", 17), 0);	
	return (1);	
}

int is_cmdline_valid(char *str)
{
	// char str[] = "$? test";
	
	if (!quote_are_closed(str))
		return(0);
	if (!are_handled_special_char(str))
		return (0);
	if (!are_pipe_and_redir_correct(str))
		return (0);
	return (1);
}
