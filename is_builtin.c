/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:03:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/07 20:14:11 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_str_digit(char *str)
{
    int i;
    
    if (!str)
        return (0); 
    i = 0;
    while(ft_isdigit(str[i]) != 0 || str[i] == '-')
        i++;
    if ((int)str[i] == 0)
        return (1);
    return(0);
    
}

int do_builtin(t_m *var, char **cmd)
{
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (ft_exit(var, cmd), 1);
    else if (ft_strcmp(cmd[0], "pwd") == 0 && go_in_builtin(cmd[1]) == 1)
        return (ft_pwd(), 1); 
    else if (ft_strcmp(cmd[0], "cd") == 0)
        return (ft_cd(cmd, 1, var), 1); 
    else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd), 1); 
    else if (ft_strcmp(cmd[0], "export") == 0) // TO DO
        return (ft_export(var, cmd), 1);
    // if (ft_strcmp(cmd[0], "unset") == 0) // TO DO
    //     return(ft_unset(cmd), 1);
    // if  (ft_strcmp(cmd[0], "env") == 0) // TO DO
    //     return(ft_echo(cmd), 1);		
    return (0);
}

int is_env_builtin(char **cmd)
{
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (1);  
    if (ft_strcmp(cmd[0], "export") == 0) // TO DO
        return (1);
    if  (ft_strcmp(cmd[0], "unset") == 0) // TO DO
        return(1);
    if  (ft_strcmp(cmd[0], "exit") == 0) // TO DO
        return(1);    
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