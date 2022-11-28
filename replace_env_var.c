/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:21 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 16:08:04 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*

les argv se convertissent directement, sauf que tu n'auras pas de argc, que des char.
Il faut donc split. Convertir ce qui peut etre converti, notamment les variables environnement (fait).
Il faut mtn l inserer ds un tout, gerer les leaks et.

Etape : split, regarder s'il y a des variables environnements pr les transformer, il faudra voir si on ameliore en mettant des categories
pour chacun : command, option, etc.

*/

// char *ft_replace_str(char **envp, int i)
// {
// 	int j = 0;
// 	int len = 0;
// 	int	k = 0;
// 	char *new_var;
	
// 	printf("c1 : %s\n", envp[i]);
// 	while(envp[i][j] != '=')
// 		j++;
// 	j++;
// 	len = strlen(envp[i]) - j;
// 	new_var = malloc(sizeof(char) * (len + 1));
// 	new_var[len] = 0;
// 	while(envp[i][j])
// 		new_var[k++] = envp[i][j++];
// 	return (new_var);
// }


// int is_in_simple_quote(char *str, int i)
// {
// 	int j = 0;

// 	while(str[j] && j < i)
// 	{
// 		if (str[j] && str[j] == 39 && j < i)
// 		{	
// 			while(str[j] && str[j] != 39)
// 				j++;
// 			if (str[j] != 0 && j > i)
// 			{
// 				// printf("waiq str[j] %c\n", str[j]);
// 				return (1);
// 			}
// 		}
// 		j++;
// 	}
// 	return (0);
// }

// void handle_environment_variables(char **str, char **envp)
// {
// 	int i[5];
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;
// 	int l = 0;
// 	char *new_str;
// 	int len = 0;
// 	char *new;
	
		

	
// 	while(envp[i])
// 	{
// 		if (ft_strncmp_minishell(str, envp[i], k, i) == 0)
// 		{	
// 			modify_string(str, envp, i)
// 			new = ft_replace_str(envp, i);
// 		}
// 		i++;
// 	}
// 	printf("final : %s\n", new);
// 	return(new);
// }
