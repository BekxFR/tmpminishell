/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:10:48 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 14:55:11 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *remove_quote(char *str, int quote, int i)
{
	int ibis = 0;

	i--;
	while(str[i] != quote)
		i--;
	ibis = i;
	while (str[i])
	{
		if (str[i] == quote)
		{	
			while (str[i+1])
			{
				str[i] = str[i+1];
				i++;
			}
			str[i] = 0;
		}
		i++;
	}
	i = ibis;
	while (str[i])
	{
		if (str[i] == quote)
		{	
			while (str[i+1])
			{	
				str[i] = str[i+1];
				i++;
			}
			str[i] = 0;
		}
		i++;
	}
	return (str);
}

char *clear_quote(char *str)
{
	int i = 0;
	int dq = 0;
	int sq = 0;
	int	j = 0;
	
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			j++;		
		i++;
	}
	if (j == 0)
		return (str);
	i = 0;
	while(str[i])
	{
		if (str[i] == 34)	
		{
			dq++;
			if (dq == 2 && (sq == 2 || sq == 0))
			{	
				str = remove_quote(str, 34, i);
				dq = 0;
				sq = 0;
				i = i - 2;
			}
		}
		else if (str[i] == 39)
		{
			sq++;
			if (sq == 2 && (dq == 2 || dq == 0))
			{
				str = remove_quote(str, 39, i);
				sq = 0;
				dq = 0;
				i = i - 2;
			}
		}
		i++;
	}
	return (str);
}

char ***clean_args(char ***cmd)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			cmd[i][j] = clear_quote(cmd[i][j]);
			j++;
		}
		i++;
	}
	return (cmd);
}
