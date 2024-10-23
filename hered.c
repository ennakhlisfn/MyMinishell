/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hered.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:25:49 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/29 18:23:16 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erw(char *lim)
{
	write(2, "bash: warning: here-document delimited by end-of-file (wanted `",
		64);
	write(2, lim, ft_strlen(lim));
	write(2, "')\n", 4);
}

void	han(int s)
{
	close(g_status);
	g_status = 130;
	write(2, "\n", 1);
	exit(130);
	s = 0;
}

void	wrihe(int fd, char *lim, t_ne *l, int co)
{
	char	*new;
	char	*line;

	line = readline(">");
	while (line && ft_strcmp(line, lim))
	{
		if (!co)
		{
			l->ili = 0;
			new = checklin(line, l);
			write(fd, new, ft_strlen(new));
			free(new);
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	if (!line)
		erw(lim);
	else
		free(line);
}

void	childnwai(int f, char *lim, t_ne *l, int co)
{
	int	st;

	if (l->lpi == 0)
	{
		g_status = f;
		signal(SIGINT, han);
		wrihe(f, lim, l, co);
		f_freex(l);
		close(f);
		exit(0);
	}
	waitpid(l->lpi, &st, 0);
	close(f);
	if (WIFEXITED(st))
	{
		l->status = WEXITSTATUS(st);
		l->ili = l->status;
	}
}

char	*generate(int co, char *lim, t_ne *l)
{
	char	*name;
	int		f;

	name = NULL;
	gename(&name);
	realbuf(name, l);
	f = open(name, O_CREAT | O_TRUNC | O_RDWR, 0400);
	signal(SIGINT, SIG_IGN);
	l->lpi = fork();
	if (l->lpi == -1)
	{
		perror("fork");
		l->status = 1;
	}
	childnwai(f, lim, l, co);
	return (name);
}
