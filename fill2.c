/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:03:35 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 17:15:53 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_redi(t_redi *redi, t_list *l, t_ne *ne)
{
	redi->dir = ft_strdup(l->args->arg);
	l->args = l->args->next;
	redi->co = l->args->co;
	redi->exp = l->args->exp;
	if (!strcmp(redi->dir, "<<"))
		redi->file = generate(l->args->co, l->args->arg, ne);
	else if (l->args->arg)
		redi->file = strdup(l->args->arg);
	if (ne->ili == 130)
		return (130);
	l->args = l->args->next;
	if (!(l->args))
		return (-1);
	return (0);
}

void	general_redi(t_redi *redi, t_list *l, t_arg *new_args, t_ne *ne)
{
	while (l->args)
	{
		while (l->args->next && (!ft_memchr(" \t\v\n\r\f><", l->args->arg[0])
				|| l->args->co))
		{
			new_args->arg = ft_strdup(l->args->arg);
			new_args->next = ft_new_arg();
			new_args = new_args->next;
			l->args = l->args->next;
		}
		if (!(l->args->next))
			break ;
		if (main_redi(redi, l, ne))
			return ;
		if (l->n_redi > 1)
		{
			redi->next = ft_new_redi();
			redi = redi->next;
			l->n_redi -= 1;
		}
	}
}

int	parenthes(t_list *list, char *line, t_ne *l)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (list->args->next)
		return (syntax_error(l), -1);
	j = l_par(line);
	if (synt_prt(line + 1))
		return (syntax_error(l) - 1);
	tmp = ft_strncopy(line + i + 1, j - 1);
	list->prt = ft_lstnew();
	if (!fill_lst(tmp, list->prt, l))
		return (free(tmp), -1);
	i += j + 1;
	while (line[i] && ft_memchr(" \t\v\n", line[i]))
		i++;
	if (!line[i] || !ft_strncmp(line + i, "&&", 2))
		return (free(tmp), i);
	if (ft_memchr("|<>", line[i]))
		return (free(tmp), i);
	return (free(tmp), syntax_error(l) - i);
}

int	ft_redirection(char *line, t_ne *l, t_arg *args, t_list *list)
{
	int	j;
	int	k;

	j = 1;
	list->n_redi++;
	if (line[0] == line[j])
	{
		if (line[0] == '<')
			l->n_here++;
		j++;
	}
	args->arg = ft_strncopy(line, j);
	args->next = ft_new_arg();
	if (!ft_strncmp(args->arg, "<<", 2))
		l->l_here = 1;
	k = fill_args(line + j, args->next, list, l);
	if (k < 0)
		return (-1);
	return (j + k);
}

int	main_expand(char *line, t_list *ls, t_arg **args, t_ne *l)
{
	if (line[ls->j] == '|' || !ft_strncmp(line + ls->j, "&&", 2))
		return (-1);
	(*args)->arg = ft_strnjoin((*args)->arg, line + ls->i, ls->j - ls->i);
	ls->i = ls->j;
	ls->j = check_qoat(line, *args, ls->j, l);
	if (ls->j > ls->i)
		ls->i = ls->j + 1;
	if (!l->l_here && line[ls->j] == '$' && (check_char(line[ls->j + 1])
			|| line[ls->j + 1] == '?'))
	{
		if (ls->i < ls->j)
			(*args)->arg = ft_strnjoin((*args)->arg, line + ls->i, ls->j
					- ls->i);
		ls->j = check_expand(line, ls, args, l);
		ls->i = ls->j + 1;
		if (line[ls->j] == '"' || line[ls->j] == '\'')
			ls->j--;
		if (line[ls->j] == '$')
			ls->i--;
		if (!line[ls->j] || ft_memchr(" \t\v\n\r\f><", line[ls->j]))
			return (-1);
	}
	return (ls->j);
}
