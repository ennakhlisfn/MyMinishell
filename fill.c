/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:55:26 by sennakhl          #+#    #+#             */
/*   Updated: 2024/08/30 15:49:48 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_token(char *line, t_list *list, t_ne *l)
{
	int	i;

	i = 0;
	while (line[i] && ft_memchr(" \t\n\v\r\f", line[i]))
		i++;
	if (line[i] == '|' || line[i] == '&')
	{
		if (line[i] == line[i + 1])
		{
			list->token = ft_strncopy(line + i, 2);
			return (i + 2);
		}
		list->token = ft_strncopy(line + i, 1);
		return (i + 1);
	}
	else if (line[i] == '(')
		return (syntax_error(l) - i);
	return (i);
}

int	main_fill(char *line, t_arg **args, t_list *list, t_ne *l)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (line[j] && !ft_memchr(" \t\v\n\r\f><(", line[j]))
	{
		list->i = i;
		list->j = j;
		if (main_expand(line, list, args, l) < 0)
			break ;
		j = list->j;
		i = list->i;
		j++;
	}
	l->l_here = 0;
	if (i < j)
		(*args)->arg = ft_strnjoin((*args)->arg, line + i, j - i);
	return (j);
}

int	fill_args(char *line, t_arg *args, t_list *list, t_ne *l)
{
	int	i;
	int	k;

	i = 0;
	k = first_skip(line, &i, list, l);
	if (k == -1)
		return (-1);
	if (k == -2)
		return (i);
	if (line[i] == '>' || line[i] == '<')
	{
		k = ft_redirection(line + i, l, args, list);
		if (k < 0)
			return (-1);
		return (i + k);
	}
	i += main_fill(line + i, &args, list, l);
	return (last_pa(line, i, list, l));
}

void	fill_redi(t_list *l, t_ne *ne)
{
	t_arg	*new_args;
	t_arg	*head;
	t_arg	*tmp;
	t_redi	*redi;

	tmp = l->args;
	new_args = ft_new_arg();
	head = new_args;
	redi = ft_new_redi();
	l->redi = redi;
	general_redi(redi, l, new_args, ne);
	ft_free_args(tmp);
	l->args = head;
	if (!l->args->arg)
	{
		ft_free_args(l->args);
		l->args = NULL;
	}
}

int	fill_lst(char *line, t_list *list, t_ne *l)
{
	int	i;
	int	j;

	i = fill_args(line, list->args, list, l);
	if (i < 0)
		return (0);
	if (list->n_redi)
		fill_redi(list, l);
	if (l->ili == 130)
		return (0);
	j = fill_token(line + i, list, l);
	if (j < 0)
		return (0);
	i += j;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (1);
	list->next = ft_lstnew();
	list = list->next;
	return (fill_lst(line + i, list, l));
}
