/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:03:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 10:44:37 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_str_digit(char *str)
{
    int i;
    
    i = 0;
    while(ft_isdigit(str[i]) != 0)
        i++;
    return((int)str[i]);
    
}

int ft_pwd(void)
{
	char *pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
        return (2);
    else
    {
        write(1, "t\n", 2);
        write(1, pwd, ft_strlen(pwd));
        write(1, "\n", 1);
	    free(pwd);
    }
    return (0);
}

int is_builtin(t_m *var, char **cmd)
{
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (ft_exit(var, cmd), 1); // PQ AFFICHE COMMAND NOT FOUND
    else if (ft_strcmp(cmd[0], "pwd") == 0 && !cmd[1])
        return (ft_pwd(), 1); 
	else if (ft_strcmp(cmd[0], "cd") == 0 && cmd[1])
        return (ft_cd(cmd, 1), 1); 
    else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd), 1); 
    else if (ft_strcmp(cmd[0], "export") == 0) // TO DO
        return (ft_export(var, cmd), 1);
    // if  (ft_strcmp(cmd[0], "unset") == 0) // TO DO
    //     return(ft_unset(cmd), 1);
    // if  (ft_strcmp(cmd[0], "env") == 0) // TO DO
    //     return(ft_echo(cmd), 1);		
    return (0);
}

// il faut les tester avec cyril pr voir pq certains trucs s'affichent!

/*

Votre shell doit implémenter les builtins suivantes :
◦ echo et l’option -n -> DONE
◦ cd uniquement avec un chemin relatif ou absolu -> DONE
◦ pwd sans aucune option -> DONE
◦ export sans aucune option ->
◦ unset sans aucune option -> 
◦ env sans aucune option ni argument _> TO DO 
◦ exit sans aucune option -> DONE

*/