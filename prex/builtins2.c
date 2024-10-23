/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:36:19 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 16:58:48 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sw(t_arg *head, t_arg *tmp, t_arg *t)
{
	head = tmp;
	tmp = head->next;
	t = head->next->next;
	head->next = t;
	tmp->next = NULL;
	free(tmp->arg);
	free(tmp);
}

static void	sw1(t_arg *head, t_arg *tmp, t_arg **v)
{
	tmp = head;
	head = head->next;
	tmp->next = NULL;
	free(tmp->arg);
	free(tmp);
	*v = head;
}

static void	unsenv(t_arg *en, t_ne *l, char **po, char *var)
{
	t_arg	*head;
	t_arg	*tmp;
	t_arg	*t;

	head = en;
	tmp = NULL;
	t = NULL;
	while (head)
	{
		getv(po, head->arg);
		if (ft_strcmp(var, "PATH") == 0)
			l->fen = 0;
		if (ft_strcmp(po[0], var) == 0)
		{
			if (tmp)
				return (sw(head, tmp, t), conver(l));
			else
				return (sw1(head, tmp, &l->en), conver(l));
		}
		tmp = head;
		head = head->next;
	}
}

static void	expunse(t_arg *e, t_ne *l, char **po, char *var)
{
	t_arg	*a;
	t_arg	*tmp;
	t_arg	*t;

	a = e;
	tmp = NULL;
	t = NULL;
	l->status = 0;
	while (a)
	{
		getv(po, a->arg);
		if (ft_strcmp(po[0], var) == 0)
		{
			if (tmp)
				return (sw(a, tmp, t));
			else
				return (sw1(a, tmp, &l->expo));
		}
		tmp = a;
		a = a->next;
	}
}

void	f_unse(t_ne *l)
{
	int		i;
	char	**po;

	f_varscore(l);
	po = fcreate(3);
	i = 0;
	i++;
	while (l->cm[i])
	{
		checkpwd(l->cm[i], l);
		if (ft_strcmp(l->cm[i], "_"))
			unsenv(l->en, l, po, l->cm[i]);
		expunse(l->expo, l, po, l->cm[i]);
		i++;
	}
	ft_frestr(po);
}
