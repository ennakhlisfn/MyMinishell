/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:19:39 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/29 18:02:18 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	initia(t_ne *l)
{
	l->status = 0;
	l->prenth = 0;
	l->n_here = 0;
	l->to = 0;
	l->ili = 0;
	l->l_here = 0;
	l->expo = NULL;
	l->fen = -1;
	l->exi = 1;
	l->inf = -2;
	l->outf = -2;
	l->cmpa = NULL;
	l->cm = NULL;
	l->env = NULL;
	l->pwd = NULL;
	l->oldpwd = NULL;
	l->larc = NULL;
	l->pa = ft_strjoin("PATH=/usr/local/sbin:/usr/local",
			"/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0);
	l->en = ft_new_arg();
}

static void	initialen(t_ne *l, t_arg *head, int i)
{
	l->fen = 1;
	l->pwd = ft_strjoin("PWD=", getcwd(NULL, 0), 1);
	l->en->arg = ft_strdup(l->pa);
	while (i < 4)
	{
		head->next = ft_new_arg();
		i++;
		head = head->next;
	}
	l->en->next->arg = ft_strdup(l->pwd);
	l->en->next->next->arg = ft_strdup("OLDPWD=");
	l->en->next->next->next->arg = ft_strdup("SHLVL=1");
	l->en->next->next->next->next->arg = ft_strdup("_=/usr/bin/env");
}

void	lvlsh(char **ar, char *e, t_ne *l)
{
	char	**tem;
	char	*t;
	int		s;

	tem = fcreate(3);
	getv(tem, e);
	s = ft_atoi(tem[1]);
	if (s >= 999)
	{
		wrerr("warning", "shell level (1000) too high, resetting to 1", 0, l);
		s = 0;
	}
	t = ft_itoa(s + 1);
	*ar = ft_strjoin("SHLVL=", t, 1);
	ft_frestr(tem);
}

void	gete(t_arg *head, char **e, int i, t_ne *l)
{
	while (e[i])
	{
		if (!ft_strncmp(e[i], "_=", 2))
		{
			l->larc = ft_strdup(e[i] + 2);
			head->arg = ft_strdup("_=/usr/bin/env");
		}
		else if (!ft_strncmp(e[i], "SHLVL=", 6))
			lvlsh(&head->arg, e[i], l);
		else
			head->arg = ft_strdup(e[i]);
		if (ft_strncmp(e[i], "PWD=", 4) == 0)
			l->pwd = ft_strdup(e[i]);
		else if (ft_strncmp(e[i], "OLDPWD=", 7) == 0)
			l->oldpwd = ft_strdup(e[i]);
		else if (ft_strncmp(e[i], "PATH=", 5) == 0)
			l->fen = 0;
		if (e[i + 1])
		{
			head->next = ft_new_arg();
			head = head->next;
		}
		i++;
	}
}

void	init(t_ne *l, char **e)
{
	int		i;
	t_arg	*head;

	i = 0;
	initia(l);
	head = l->en;
	if (!e || !*e)
		initialen(l, head, i);
	else
	{
		gete(head, e, i, l);
		if (l->fen == -1)
		{
			head = ft_new_arg();
			head->next = l->en;
			l->en = head;
			head->arg = ft_strdup(l->pa);
			l->fen = 1;
		}
	}
	conver(l);
	iniexpo(l);
}
