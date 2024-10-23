/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:39:00 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/01 18:08:05 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status = 0;

void	ini(t_ne *l)
{
	l->p = 0;
	l->to = 0;
	l->lpi = 0;
}

void	hand(int s)
{
	(void)s;
	if (g_status == 2)
		write(1, "\n", 1);
	g_status = 130;
}

char	*fill_tmp(char *line)
{
	char	*t;

	t = NULL;
	if (line)
		t = ft_memchr(line, '\n');
	if (t)
		return (ft_strdup(t + 1));
	return (NULL);
}

int	minihell(t_ne *l, t_list *list, char **line, char **tmp)
{
	t_list	head;

	if (!*tmp)
		ge_line(line, l, list);
	else
	{
		*line = *tmp;
		*tmp = NULL;
	}
	*tmp = fill_tmp(*line);
	if (*line)
		*line = ft_separate(*line, '\n');
	if (*line && parsing(*line, list, l))
	{
		ini(l);
		head = *list;
		signal(SIGINT, hand);
		ftexec(&head, l);
		if (l->exi)
			g_status = 0;
	}
	clof(l);
	return (check_free(line, l, list));
}

int	main(int arc, char *arv[], char **env)
{
	t_list	*list;
	char	*line;
	char	*tmp;
	t_ne	l;

	(void)arc, (void)arv;
	tmp = NULL;
	line = NULL;
	init(&l, env);
	while (1)
	{
		list = ft_lstnew();
		l.he = 0;
		l.buf = NULL;
		if (minihell(&l, list, &line, &tmp))
			break ;
	}
	endm(tmp, line, list, &l);
}
