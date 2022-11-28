/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:55:46 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 16:48:28 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_index initialize_index()
{
	t_index	i;

	i.i = 0;
	i.i1 = 0;
	i.i2 = 0;
	i.i3 = 0;
	i.j = 0;
	i.j1 = 0;
	i.j2 = 0;
	i.j3 = 0;
	i.start = 0;
	i.end = 0;
	i.count = 0;
	i.k = 0;
	i.t = 0;
	i.l = 0;
	i.counter = 0;
	i.len = 0;	
	return (i);
}
