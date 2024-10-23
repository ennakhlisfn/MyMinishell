/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:09:02 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/01 16:43:57 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	i = 0;
	if (s == NULL)
		return (ft_strdup(""));
	l = ft_strlen(s);
	if (start >= l)
		len = 0;
	if (len > l - start)
		len = l - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

static int	countword(char const *s, char c)
{
	int	i;
	int	cnt;
	int	oi;

	oi = 0;
	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			i++;
			if (s[i] == c || !s[i])
				cnt++;
		}
		oi = i;
		while (s[oi] == c && s[i])
		{
			oi++;
			i++;
		}
	}
	return (cnt);
}

static char	**ft_fre(char **str, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**ft_su(char **str, char const *s, char c, int cnt)
{
	int	i;
	int	j;
	int	oi;

	i = 0;
	j = 0;
	while (s[i] && j < cnt)
	{
		oi = i;
		while (s[oi] == c)
			oi++;
		i = oi;
		while (s[i] != c && s[i])
			i++;
		if (oi < i)
		{
			str[j] = ft_substr(s, oi, i - oi);
			if (str[j] == NULL)
				return (ft_fre(str, j));
			j++;
		}
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = countword(s, c) + 1;
	str = malloc(cnt * sizeof(char *));
	if (!str)
		return (NULL);
	str = ft_su(str, s, c, cnt);
	return (str);
}
