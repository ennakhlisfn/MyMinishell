/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hered2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:12:39 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/01 16:36:04 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gename(char **buf)
{
	int		f;
	int		j;
	char	*arr;
	char	b[12];
	char	bu[12];

	arr = ft_strdup("0123456789abcdef");
	f = open("/dev/random", O_RDONLY);
	b[11] = '\0';
	read(f, b, 11);
	j = 0;
	while (j < 11)
	{
		bu[j] = arr[(unsigned char)b[j] % 16];
		j++;
	}
	bu[j] = 0;
	*buf = ft_strjoin("/tmp/.", bu, 0);
	close(f);
	free(arr);
}

char	*get_li(char *line, int *i, int j, t_ne *l)
{
	char	*t;
	char	*tmp;
	char	*get;

	*i = *i + 1;
	if (line[*i] == '?')
	{
		*i = *i + 1;
		return (ft_itoa(l->status));
	}
	if (line[*i] == '_')
	{
		*i = *i + 1;
		return (ft_strdup(l->larc));
	}
	while (line[*i] && check_char(line[*i]))
		*i = *i + 1;
	t = ft_strncopy(line + j, *i - j);
	tmp = ft_strjoin(t, "=", 0);
	get = ft_getenv(tmp, l);
	ft_free(t);
	ft_free(tmp);
	return (get);
}

void	getl(char **re, char *line, int *i, t_ne *l)
{
	char	*t;
	char	*tem;
	char	*get;
	int		j;

	j = l->ili;
	if (!*re)
		t = ft_strncopy(line, *i);
	else
	{
		tem = ft_strncopy(line + j, *i - j);
		t = ft_strjoin(*re, tem, 1);
		free(*re);
	}
	j = *i + 1;
	get = get_li(line, i, j, l);
	*re = ft_strjoin(t, get, 0);
	free(t);
	if (get)
		free(get);
}

char	*checklin(char *line, t_ne *l)
{
	int		i;
	char	*re;
	char	*li;
	char	*t;

	i = 0;
	li = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			getl(&li, line, &i, l);
			l->ili = i;
			i--;
		}
		if (!line[i])
			break ;
		i++;
	}
	t = ft_strncopy(line + l->ili, i - l->ili);
	re = ft_strjoin(li, t, 0);
	free(li);
	free(t);
	return (re);
}
