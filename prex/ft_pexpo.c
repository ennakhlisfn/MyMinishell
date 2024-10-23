/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pexpo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:38:00 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 17:01:52 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checktem(char **tem, t_ne *l, int *p)
{
	char	*tp;
	int		len;

	tp = NULL;
	if (!ft_strcmp(tem[0], "_"))
		return (1);
	len = ft_strlen(tem[0]);
	if (tem[0][len - 1] == '+')
	{
		len--;
		tp = ft_strdup(tem[0]);
		free(tem[0]);
		tem[0] = ft_strncopy(tp, len);
		*p = 1;
		free(tp);
	}
	if (check_pth(tem, l, p))
		return (1);
	return (0);
}

void	get_max(char **tem, t_arg *expo)
{
	t_arg	*he;
	char	**p;

	p = fcreate(3);
	he = expo;
	getv(tem, he->arg);
	while (he)
	{
		getv(p, he->arg);
		if (ft_strcmp(tem[0], p[0]) < 0)
			getv(tem, he->arg);
		he = he->next;
	}
	ft_frestr(p);
}

void	pr(char **tem, char **mini, int *i)
{
	printf("declare -x		%s", tem[0]);
	if (tem[1])
		printf("=\"%s\"\n", tem[1]);
	else
		printf("\n");
	ft_free(*mini);
	*mini = ft_strdup(tem[0]);
	*i = *i + 1;
}

void	pexpo(t_ne *l)
{
	t_arg	*head;
	char	*mini;
	char	**p;
	char	**tem;

	mini = NULL;
	p = fcreate(3);
	tem = fcreate(3);
	l->ili = 0;
	while (l->ili < ft_lstsize(l->expo))
	{
		head = l->expo;
		get_max(tem, head);
		while (head)
		{
			getv(p, head->arg);
			if (l->ili == 0 && ft_strcmp(tem[0], p[0]) > 0)
				getv(tem, head->arg);
			else if (ft_strcmp(tem[0], p[0]) > 0 && ft_strcmp(p[0], mini) > 0)
				getv(tem, head->arg);
			head = head->next;
		}
		pr(tem, &mini, &l->ili);
	}
	return (ft_free(mini), ft_frestr(p), ft_frestr(tem));
}

void	f_expo(t_ne *l)
{
	t_arg	*h;
	int		i;

	i = 0;
	f_varscore(l);
	if (parlen(l->cm) == 1)
		pexpo(l);
	else
	{
		i++;
		while (l->cm[i])
		{
			if (l->cm[i] && isvalid(l->cm[i], l))
			{
				h = ft_new_arg();
				h->arg = ft_strdup(l->cm[i]);
				h->next = l->expo;
				l->expo = h;
			}
			i++;
		}
	}
}
