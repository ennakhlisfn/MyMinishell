/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:59:55 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 16:49:59 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_pwd(t_ne *l)
{
	char	*d;
	int		len;

	f_varscore(l);
	len = parlen(l->cm);
	if (len > 1 && ft_strncmp(l->cm[1], "-", 1) == 0)
	{
		write(2, "bash: pwd: ", 12);
		write(2, l->cm[1], ft_strlen(l->cm[1]));
		write(2, ": invalid option\n", 18);
		l->status = 2;
		return ;
	}
	d = getcwd(NULL, 0);
	if (d == NULL)
	{
		write(2, "bash: pwd: error in getting the current directory\n", 51);
		l->status = 1;
		return ;
	}
	printf("%s\n", d);
	free(d);
}

void	f_env(t_ne *l)
{
	int	nar;
	int	i;

	f_varscore(l);
	i = 0;
	nar = parlen(l->cm);
	if (nar > 1)
	{
		if (ft_strncmp(l->cm[1], "-", 1) == 0)
		{
			write(2, "env: invalid option\n", 21);
			l->status = 125;
		}
		else
		{
			write(2, "invalid arg\n", 13);
			l->status = 1;
		}
		return ;
	}
	while (l->env && l->env[i])
	{
		printf("%s\n", l->env[i]);
		i++;
	}
}

static int	echon(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	normecho(int f, int le, int i, t_ne *l)
{
	while (l->cm && l->cm[i])
	{
		if (f < le)
			write(1, " ", 1);
		write(1, l->cm[i], ft_strlen(l->cm[i]));
		i++;
		f--;
	}
}

void	f_echo(t_ne *l)
{
	int	i;
	int	le;
	int	n;
	int	f;

	f_varscore(l);
	n = 0;
	i = 0;
	l->status = 0;
	le = parlen(l->cm);
	f = le;
	i++;
	while (l->cm && ft_strncmp(l->cm[i], "-n", 2) == 0)
	{
		if (echon(l->cm[i]) == 1)
		{
			i++;
			n = 1;
		}
		else
			break ;
	}
	normecho(f, le, i, l);
	if (n == 0)
		write(1, "\n", 1);
}
