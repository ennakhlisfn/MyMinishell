/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:51:29 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/26 18:08:59 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	l;
	int		i;

	i = 0;
	l = ft_strlen(s1) + 1;
	p = NULL;
	if (s1)
	{
		p = (char *)malloc(l * sizeof(char));
		if (!p)
			return (NULL);
		while (s1[i])
		{
			p[i] = s1[i];
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}

int	parlen(char **par)
{
	int	i;

	i = 0;
	if (!par)
		return (i);
	while (par && par[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	if (d == s)
		return (d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char *s2, int f)
{
	size_t	all;
	char	*p;
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && *s2)
		return (ft_strdup(s2));
	if (!s2 && *s1)
		return (ft_strdup(s1));
	all = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(all * sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s1, ft_strlen(s1));
	while (s2 && s2[i])
	{
		p[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	p[ft_strlen(s1) + i] = '\0';
	if (f && s2)
		free(s2);
	return (p);
}
