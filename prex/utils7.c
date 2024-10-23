/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:03:06 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 17:46:15 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isdire(char *f)
{
	DIR	*d;

	d = opendir(f);
	if (d)
	{
		closedir(d);
		return (1);
	}
	return (0);
}

void	subpipe(t_list *lst, t_ne *l)
{
	int	t;

	t = l->p;
	l->p = 0;
	l->prenth = 1;
	l->to = 0;
	ftexec(lst, l);
	l->to = 1;
	l->prenth = 0;
	l->p = t;
}

void	changepwd(char **tem, t_ne *l)
{
	if (!ft_strcmp(tem[0], "PWD"))
	{
		if (l->pwd)
			free(l->pwd);
		l->pwd = ft_strjoin("PWD=", tem[1], 0);
	}
	else if (!ft_strcmp(tem[0], "OLDPWD"))
	{
		if (l->oldpwd)
			free(l->oldpwd);
		l->oldpwd = ft_strjoin("OLDPWD=", tem[1], 0);
	}
}

void	check_pwd(char **tem, int p, t_ne *l)
{
	char	*t;

	if (p)
	{
		if (!ft_strcmp(tem[0], "PWD"))
		{
			t = l->pwd;
			l->pwd = ft_strjoin(t, tem[1], 0);
			if (t)
				free(t);
		}
		else if (!ft_strcmp(tem[0], "OLDPWD"))
		{
			t = l->oldpwd;
			l->oldpwd = ft_strjoin(t, tem[1], 0);
			if (t)
				free(t);
		}
	}
	else
		changepwd(tem, l);
}
