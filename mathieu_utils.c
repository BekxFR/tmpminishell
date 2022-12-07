/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathieu_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:36:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 18:06:54 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

int		ft_intlen(int nbr)
{
	int int_len;

	int_len = 0;
	if (nbr < 0)
		int_len++;
	else if (nbr == 0)
		return (1);
	else
		nbr = -nbr;
	while (nbr < 0)
	{
		nbr /= 10;
		int_len++;
	}
	return (int_len);
}

int	ft_strlenint(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_strcmplen(char ***redir, char *str)
{
    int i;
    int j;
    int k;

    k = 0;
    i = 0;
    while(redir[i])
    {
        j = 0;
        while(redir[i][j])
        {
            if (strcmp(redir[i][j], str) == 0)
                k++;
            j++;
        }
        i++;
    }
    return (k);   
}