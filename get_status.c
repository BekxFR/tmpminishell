/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:11:45 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 19:12:00 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_status(char *str, int end, int start, char *status)
{
	t_index	i;
	char	*newstring;
	char	*env;

	i = initialize_index();
	i.count = end - start;
	i.len = ft_strlen(str) - (i.count + 1) + ft_strlen(status);
	env = ft_calloc(sizeof(char), (ft_strlen(status) + 1));
	env = ft_strcpy(env, status);
	(void)i;
	newstring = ft_calloc(sizeof(char), (i.len + 1));
	while (str[i.i1])
	{
		while (str[i.i1] && i.i1 != (start - 1))
			newstring[i.i2++] = str[i.i1++];
		while (env[i.i3])
			newstring[i.i2++] = env[i.i3++];
		i.i1 = i.i1 + i.count + 1;
		while (str[i.i1])
			newstring[i.i2++] = str[i.i1++];
	}
	free(str);
	return (newstring);
}
