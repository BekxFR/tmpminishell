/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathieu_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:36:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 18:50:14 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putdoubletab(char **tab)
{
	static int j = 0;
	int	i;

	i = 0;
	if (!tab)
		return ;
	printf("command %i :\n", j++);
	while (tab[i])
	{
		ft_putstr(tab[i]);
		write(1, "\n", 1);
		i++;
	}	
}

void	ft_puttripletab(char ***test)
{
	int i ; 

	i = 0;
	if (!test)
		return ;
	while(test[i])
	{
		ft_putdoubletab(test[i]);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_tablen(char **tab)
{	
	int	y;

	y = 0;
	while (tab[y])
	{
		y++;
	}
	return (y);
}
