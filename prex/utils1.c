/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:26:43 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/26 15:49:17 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str, t_ne *l)
{
	int		len;
	char	*get;
	t_arg	*head;

	get = NULL;
	len = ft_strlen(str);
	head = l->en;
	while (head)
	{
		if (ft_strncmp(str, head->arg, len) == 0)
		{
			get = ft_strdup(head->arg + len);
			break ;
		}
		else
			head = head->next;
	}
	return (get);
}

void	ft_frestr(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str[i]);
		free(str);
		str = NULL;
	}
}

void	ft_frecmd(t_ne *l)
{
	if (l->cm)
		ft_frestr(l->cm);
	if (l->cmpa)
	{
		free(l->cmpa);
		l->cmpa = NULL;
	}
}

void	f_freex(t_ne *l)
{
	if (l->larc)
		free(l->larc);
	if (l->pa)
		free(l->pa);
	if (l->pwd)
		free(l->pwd);
	if (l->oldpwd)
		free(l->oldpwd);
	ft_free_args(l->en);
	ft_free_args(l->expo);
	ft_frestr(l->env);
}

void	getv(char **tem, char *st)
{
	int	i;

	i = 0;
	if (tem[0])
	{
		free(tem[0]);
		tem[0] = NULL;
	}
	if (tem[1])
	{
		free(tem[1]);
		tem[1] = NULL;
	}
	while (st[i])
	{
		if (st[i] == '=')
			break ;
		i++;
	}
	tem[0] = ft_strncopy(st, i);
	if (st[i] == '=')
		tem[1] = ft_strdup(st + i + 1);
}
