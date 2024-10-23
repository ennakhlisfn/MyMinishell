/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:33:41 by sennakhl          #+#    #+#             */
/*   Updated: 2024/08/28 20:40:38 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_a(char *a, int n, int p)
{
	int	i;

	i = 0;
	while (p > 1)
	{
		p /= 10;
		a[i++] = n / p + '0';
		n %= p;
	}
	a[i] = 0;
	return (a);
}

char	*ft_itoa(int n)
{
	int		i;
	int		tmp;
	int		p;
	char	*a;

	i = 0;
	tmp = n;
	p = 1;
	while (tmp || !i)
	{
		tmp /= 10;
		p *= 10;
		i++;
	}
	a = (char *)malloc((i + 1) * sizeof(char));
	if (!a)
		return (NULL);
	return (fill_a(a, n, p));
}

char	*ft_separate(char *line, char sep)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != sep)
		i++;
	if (!line[i])
		return (line);
	tmp = (char *)malloc((i + 2) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != sep)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i++] = sep;
	tmp[i] = 0;
	free(line);
	return (tmp);
}

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s1 && s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && j < n)
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	tmp[i] = 0;
	free(s1);
	return (tmp);
}

char	*ft_strncopy(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src)
		return (NULL);
	dest = (char *)malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
