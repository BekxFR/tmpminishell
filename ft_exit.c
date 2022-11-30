/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/14 17:41:13 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
Faut-il que ca exit la page shell ou juste notre programm shell ?

*/

int ft_exit(void)
{
	exit (0);
}

int main(void)
{
	ft_exit();	
	return (0);
}
