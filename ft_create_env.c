/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:14:54 by chillion          #+#    #+#             */
/*   Updated: 2022/12/13 10:43:34 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_create_env(t_m *var, char **envp)
{
	int	i;

	if (!envp)
	{
		(*var).env = (char **)malloc(sizeof(char *) * 1);
		if (!(*var).env)
			return (-1);
		(*var).env[0] = (char *)malloc(sizeof(char) * 1);
		if (!(*var).env[0])
			return (free((*var).env), -1);
		(*var).env[0][0] = 0;
		(*var).env[0] = 0;
		return (1);
	}
	i = 0;
	while (envp[i])
		i++;
	(*var).env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*var).env)
		return (-1);
	(*var).env[i] = 0;
	i = -1;
	while (envp[++i])
		(*var).env[i] = ft_strdup(envp[i]);
	return (0);
}

void	ft_print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	*ft_strdup_without_one(const char *src)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dest;

	j = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (j));
	if (!dest)
		return (NULL);
	dest[j - 1] = '\0';
	k = 0;
	while (src[k] && src[k] != '+')
		k++;
	i = 0;
	j = 0;
	while (src[i])
	{
		if (i == k)
			j++;
		dest[i] = src[i + j];
		i++;
	}
	return (dest);
}

int	ft_export_check_args(char *args, int *egalen)
{
	if (!args && !*args)
		return (0);
	if ((ft_isalpha(args[0]) == 0) && args[0] != '_')
	{
		g_exit_status = 1;
		return (write(2, "export: `", 10), ft_putstr_fd(args, 2), \
		write(2, "': not a valid identifier\n", 27), 0);
	}
	*egalen = -1;
	while ((++*egalen) > -1 && args[(*egalen)] && (args[(*egalen) + 1] != '='))
	{
		if (args[*egalen] != '_' && (ft_isalnum(args[*egalen]) == 0))
		{
			g_exit_status = 1;
			return (write(2, "export: `", 10), ft_putstr_fd(args, 2), \
			write(2, "': not a valid identifier\n", 27), 0);
		}
	}
	if (args[*egalen] == '\0')
		return (0);
	return ((++*egalen));
}

int	ft_export_check_addargs(char *args, int *egalen)
{
	if (!args && !*args)
		return (0);
	if ((ft_isalpha(args[0]) == 0) && args[0] != '_')
		return (write(2, "export: `", 10), ft_putstr_fd(args, 2), \
		write(2, "': not a valid identifier\n", 27), -1);
	*egalen = -1;
	while ((++*egalen) > -1 && args[(*egalen)] && (args[(*egalen)] != '='))
	{
		if (args[(*egalen) + 1] == '=' && args[(*egalen)] == '+')
		{
			if (args[(*egalen) + 2] != '\0')
				return (*egalen);
		}
		if (args[*egalen] != '_' && (ft_isalnum(args[*egalen]) == 0))
			return (write(2, "export: `", 10), ft_putstr_fd(args, 2), \
			write(2, "': not a valid identifier\n", 27), 0);
	}
	if (args[*egalen] == '\0')
		return (-2);
	return (0);
}
