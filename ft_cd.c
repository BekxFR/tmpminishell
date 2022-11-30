/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/14 17:32:13 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Subject : Reproduction of cd function
It handles :
- cd par des chemins relatifs (cd .., cd dir_after)
- cd par chemin absolu

*/
int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		l;
	char	*s3;

	i = 0;
	l = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (free(s1), NULL);
	while (s1[i])
	{
		s3[l] = s1[i];
		i++;
		l++;
	}
	i = 0;
	while (s2[i])
		s3[l++] = s2[i++];
	s3[l] = '\0';
	return (free(s1), s3);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int ft_cd(char **argv, int i)
{
	char	*path;
	char	*newpath;
	int		pathlen;
		
	path = NULL;
	newpath = NULL;
	path = getcwd(path, 0);
	printf("%s\n", path);
	pathlen = strlen(path);
	if (!argv[i])
	{
		printf("handle later\n");
		return (0);
	}
	if (argv[i][0] != '/')
	{
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, argv[i]);
		if (chdir(path) != 0)
			printf("Error\n");
		printf("%s\n", path);
	}
	else 
	{
		if (chdir(argv[i]) != 0)
			printf("Error\n");
		printf("test\n");
	}
	printf("c1\n");
	newpath = getcwd(newpath, 0);
	printf("%s\n", newpath);
	return (0);
}

int main(int argc, char **argv)
{
	int i;
	
	i = 0;
	ft_cd(argv, (i + 1));
	return (0);
}