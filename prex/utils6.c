/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:05:04 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/01 10:05:43 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *str, const char *fd, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str && len == 0 && *fd)
		return (NULL);
	if (!*fd)
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (str[i] == fd[j] && i < len)
		{
			j++;
			i++;
			if (fd[j] == '\0')
				return ((char *)str + i - j);
		}
		i = i - j + 1;
		j = 0;
	}
	return (NULL);
}

int	checkam(t_redi *head, t_ne *l, int *err)
{
	char	*file;

	if (!*err)
	{
		file = head->file;
		if (head->exp)
		{
			if (!file || isther(file, ' ') || isther(file, '\n') || isther(file,
					'\t'))
			{
				l->inf = -2;
				l->outf = -2;
				return (wrerr(NULL, "ambiguous redirect", 1, l), 1);
			}
		}
	}
	return (0);
}

void	addinpth(t_arg *ar, t_ne *l, int s)
{
	t_arg	*h;

	if (s)
	{
		h = ft_new_arg();
		h->arg = ft_strdup(l->pa);
		h->next = l->expo;
		l->expo = h;
	}
	else
	{
		h = ar;
		while (h)
		{
			if (!ft_strncmp("PATH=", h->arg, 5))
			{
				free(h->arg);
				h->arg = ft_strdup(l->pa);
			}
			h = h->next;
		}
	}
}

int	check_pth(char **tem, t_ne *l, int *p)
{
	char	*t;

	if (!ft_strcmp(tem[0], "PATH") && l->fen == 1)
	{
		if (*p == 1)
		{
			t = ft_strdup(l->pa);
			free(l->pa);
			l->pa = ft_strjoin(t, tem[1], 0);
			free(t);
		}
		else
		{
			free(l->pa);
			l->pa = ft_strjoin("PATH=", tem[1], 0);
		}
		l->fen = 0;
		addinpth(l->expo, l, 1);
		addinpth(l->en, l, 0);
		conver(l);
		return (1);
	}
	return (0);
}

void	expoadd(t_arg *e, char **tem)
{
	char	**t;
	char	*te;
	char	*tp;

	t = fcreate(3);
	getv(t, e->arg);
	free(e->arg);
	te = ft_strjoin(t[0], "=", 0);
	tp = ft_strjoin(te, t[1], 0);
	e->arg = ft_strjoin(tp, tem[1], 0);
	free(te);
	free(tp);
	ft_frestr(t);
}
