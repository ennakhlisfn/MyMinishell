/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exputil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:36:42 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/26 18:08:53 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isther(char *st, char c)
{
	int	i;

	i = 0;
	while (st[i] && st[i] != '=')
	{
		if (st[i] == c)
			return (1);
		i++;
	}
	if (st[i] && st[i] == '=' && c == '=')
		return (1);
	return (0);
}

int	checkvales(char *st)
{
	int	i;

	i = 1;
	if (ft_isalpha(st[0]) || st[0] == '_')
	{
		while (st[i])
		{
			if (ft_isalpha(st[i]) || ft_isdigit(st[i]) || st[i] == '_')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	checkval(char *st)
{
	int	i;

	i = 1;
	if (isther(st, '='))
	{
		if (ft_isalpha(st[0]) || st[0] == '_')
		{
			while (st[i] && st[i] != '=')
			{
				if (ft_isalpha(st[i]) || ft_isdigit(st[i]) || st[i] == '_')
					i++;
				else if (st[i] == '+' && st[i + 1] == '=')
					return (0);
				else
					return (1);
			}
			return (0);
		}
	}
	return (checkvales(st));
}

int	isvalid(char *st, t_ne *l)
{
	if (st[0] == '-' && ft_strlen(st) <= 2)
	{
		wrerr(&st[1], ": invalid option", 2, l);
		return (0);
	}
	if (isther(st, '-'))
	{
		wrerr(st, ": not a valid identifier", 1, l);
		return (0);
	}
	if (!checkval(st))
	{
		if (isexist(st, l) != 0)
			return (0);
		else
			return (1);
	}
	else
	{
		wrerr(st, ": not a valid identifier", 1, l);
		return (0);
	}
}

int	addexpo(char *st, t_ne *l)
{
	t_arg	*o;

	o = l->expo;
	while (o && o->arg)
	{
		if (ft_strncmp(st, o->arg, ft_strlen(st)) == 0)
			return (1);
		o = o->next;
	}
	return (0);
}
