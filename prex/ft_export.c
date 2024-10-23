/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:34:29 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 17:46:07 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkenv(t_arg *e, int p, int *i, char *st)
{
	char	**tem;

	tem = fcreate(3);
	getv(tem, st);
	if (p)
		expoadd(e, tem);
	else
	{
		free(e->arg);
		e->arg = ft_strdup(st);
	}
	*i = *i + 1;
	ft_frestr(tem);
}

void	addenv(t_arg **a, char **tem, int *i)
{
	t_arg	*e;
	char	*tp;

	e = ft_new_arg();
	tp = ft_strjoin("=", tem[1], 0);
	e->arg = ft_strjoin(tem[0], tp, 1);
	e->next = *a;
	*a = e;
	*i = *i + 1;
}

int	expenv(char *st, char **tem, t_ne *l, int p)
{
	t_arg	*e;
	char	**po;
	int		i;

	i = 0;
	e = l->en;
	po = fcreate(3);
	while (e && e->arg)
	{
		getv(po, e->arg);
		if (!ft_strcmp(po[0], tem[0]))
		{
			checkenv(e, p, &i, st);
			break ;
		}
		e = e->next;
	}
	if (!i)
		addenv(&l->en, tem, &i);
	ft_frestr(po);
	return (i);
}

int	expexp(char *st, char **tem, t_ne *l, int p)
{
	t_arg	*e;
	char	**po;
	int		i;

	i = 0;
	e = l->expo;
	po = fcreate(3);
	while (e && e->arg)
	{
		getv(po, e->arg);
		if (!ft_strcmp(po[0], tem[0]))
		{
			checkenv(e, p, &i, st);
			break ;
		}
		e = e->next;
	}
	if (!i)
		addenv(&l->expo, tem, &i);
	ft_frestr(po);
	return (i);
}

int	isexist(char *st, t_ne *l)
{
	char	**tem;
	int		i;
	int		p;

	i = 0;
	p = 0;
	tem = fcreate(3);
	if (isther(st, '='))
	{
		getv(tem, st);
		if (checktem(tem, l, &p))
			return (1);
		check_pwd(tem, p, l);
		i += expenv(st, tem, l, p);
		conver(l);
		i += expexp(st, tem, l, p);
	}
	else
		i += addexpo(st, l);
	ft_frestr(tem);
	return (i);
}
