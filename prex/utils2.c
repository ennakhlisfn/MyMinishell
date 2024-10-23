/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:17:06 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 16:46:26 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	iniexpo(t_ne *l)
{
	int		i;
	t_arg	*head;

	i = 0;
	l->expo = ft_new_arg();
	head = l->expo;
	while (l->env[i])
	{
		if (ft_strncmp(l->env[i], "_=", 2))
			head->arg = ft_strdup(l->env[i]);
		i++;
		if (l->env[i] && ft_strncmp(l->env[i], "_=", 2))
		{
			head->next = ft_new_arg();
			head = head->next;
		}
	}
	if (l->fen == 1)
	{
		head->next = ft_new_arg();
		head->next->arg = ft_strdup("OLDPWD");
	}
}

void	wrerr(char *c, char *er, int s, t_ne *l)
{
	write(2, "minishell: ", 12);
	if (c)
	{
		write(2, c, ft_strlen(c));
		write(2, ": ", 2);
	}
	if (er)
	{
		write(2, er, ft_strlen(er));
		write(2, "\n", 1);
	}
	l->status = s;
}

char	**fcreate(int s)
{
	char	**p;
	int		i;

	i = 0;
	p = malloc(s * sizeof(char *));
	while (i < s)
	{
		p[i] = NULL;
		i++;
	}
	return (p);
}

void	f_varscore(t_ne *l)
{
	int	i;

	i = parlen(l->cm);
	if (l->larc)
	{
		free(l->larc);
		l->larc = NULL;
	}
	l->larc = ft_strdup(l->cm[i - 1]);
}

void	update(t_ne *l)
{
	t_arg	*t;

	t = l->expo;
	while (t)
	{
		if (!ft_strncmp(t->arg, "PWD=", 4))
		{
			free(t->arg);
			t->arg = ft_strdup(l->pwd);
		}
		else if (!ft_strncmp(t->arg, "OLDPWD=", 7))
		{
			free(t->arg);
			t->arg = ft_strdup(l->oldpwd);
		}
		else if (!ft_strncmp(t->arg, "OLDPWD", 6) && l->fen == 1)
		{
			free(t->arg);
			t->arg = ft_strdup(l->oldpwd);
		}
		t = t->next;
	}
}
