/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:58:06 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/03 11:23:02 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swits(t_ne *l, char *new)
{
	if (l->oldpwd)
	{
		free(l->oldpwd);
		l->oldpwd = NULL;
	}
	if (l->pwd)
		l->oldpwd = ft_strjoin("OLDPWD=", l->pwd + 4, 0);
	else
		l->oldpwd = ft_strdup("OLDPWD=");
	if (l->pwd)
	{
		free(l->pwd);
		l->pwd = NULL;
	}
	l->pwd = ft_strjoin("PWD=", getcwd(NULL, 0), 1);
	conver(l);
	update(l);
	l->status = 0;
	if (new)
		free(new);
}

static void	norm(t_ne *l, char *home)
{
	if (chdir(home) == -1)
		return (wrerr("cd", NULL, 1, l), perror(home), free(home));
	return (swits(l, home));
}

void	f_cd(t_ne *l)
{
	char	*home;
	int		s;

	f_varscore(l);
	s = parlen(l->cm);
	if (s == 1)
	{
		home = ft_getenv("HOME=", l);
		if (!home)
			return (wrerr("cd", "HOME not set", 1, l));
		else
			return (norm(l, home));
	}
	else if (s > 2)
		return (wrerr("cd", "too many arguments", 1, l));
	if (ft_strncmp(l->cm[1], "-", 1) == 0)
		return (wrerr("cd", "invalid option", 2, l));
	if (ft_strlen(l->cm[1]) && chdir(l->cm[1]) == -1)
		return (wrerr("cd", NULL, 1, l), perror(l->cm[1]));
	swits(l, NULL);
}

static void	checkex(t_ne *l, int n)
{
	l->status = n;
	if (l->exi)
		exit(l->status);
}

void	f_exit(t_ne *l)
{
	unsigned long	n;
	int				a;

	printf("exit\n");
	if (l->cm[1])
	{
		a = ft_atol(l->cm[1], &n);
		if (a == 2)
		{
			wrerr("exit", "numeric argument required", 2, l);
			checkex(l, l->status);
		}
		else if (l->cm[2])
		{
			if (!l->exi)
				l->exi = 1;
			wrerr("exit", "too many arguments", 1, l);
		}
		else
			checkex(l, n);
	}
	else
		checkex(l, l->status);
}
