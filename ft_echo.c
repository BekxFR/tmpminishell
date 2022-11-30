/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:44:01 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/14 15:13:01 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
Subject : reproduction of echo function 

It handles several cases :
echo -n XXX
echo -nnnnnn (which works the same as echo -n) (no matter the number of n)
echo -nXXXX (which)
echo XXXXX
echo $USER (printf handle this behaviour)
echo '$USER'
echo "$USER"

*/

int	is_n_option(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
}

void	ft_echo_with_n_option(char **argv, int i, int argc)
{
	i++;
	if (!argv[i])
		return ;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (i + 1 != argc)
			printf(" ");
		i++;
	}
	return ;
}

void	ft_echo_without_n_option(char **argv, int i, int argc)
{
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (i + 1 != argc)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_echo(char **argv, int i, int argc)
{
	if (!argv[i])
	{
		printf("\n");
		return ;
	}
	if (is_n_option(argv[i]) == 0)
	{
		ft_echo_with_n_option(argv, i, argc);
		return ;
	}
	ft_echo_without_n_option(argv, i, argc);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	ft_echo(argv, (i + 1), argc);
	return (0);
}
