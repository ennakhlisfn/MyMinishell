/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:49:14 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/26 18:16:29 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clof(t_ne *l)
{
	int	i;

	i = 0;
	while (i < l->he)
	{
		if (!access(l->buf[i], F_OK))
			unlink(l->buf[i]);
		i++;
	}
	ft_frestr(l->buf);
}

void	clos(int *i)
{
	if (*i != -2)
	{
		close(*i);
		*i = -2;
	}
}

void	f_dupstr(char **ar, char *n)
{
	if (*ar)
		free(*ar);
	*ar = ft_strdup(n);
}

void	dupenv(t_arg *head, t_ne *l)
{
	int	i;

	i = 0;
	while (head)
	{
		if (l->fen == 1 && ft_strncmp(head->arg, "PATH=", 5) == 0)
		{
			head = head->next;
			if (!head)
				break ;
		}
		if (ft_strncmp(head->arg, "PWD=", 4) == 0)
			f_dupstr(&head->arg, l->pwd);
		else if (ft_strncmp(head->arg, "OLDPWD=", 7) == 0)
		{
			if (l->oldpwd)
				f_dupstr(&head->arg, l->oldpwd);
			else
				head = head->next;
		}
		l->env[i] = ft_strdup(head->arg);
		head = head->next;
		i++;
	}
}

void	conver(t_ne *l)
{
	t_arg	*head;
	int		le;

	head = l->en;
	le = ft_lstsize(l->en) + 1;
	ft_frestr(l->env);
	if (l->fen == 1)
		le -= 1;
	if (!l->oldpwd && l->fen == 1)
		le -= 1;
	l->env = fcreate(le);
	dupenv(head, l);
}
