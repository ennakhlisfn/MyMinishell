/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:56:13 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 19:53:44 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_white(char *line)
{
	int	i;

	i = 0;
	while (line[i] && check_char(line[i]))
	{
		if (!ft_strncmp(line + i, "&&", 2))
			return (i);
		i++;
	}
	return (i);
}

void	add_args(char *tmp, t_arg **args)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		(*args)->arg = ft_strnjoin((*args)->arg, tmp + i, 1);
		i++;
		if (ft_memchr(" \t\r\v\f\n", tmp[i]))
		{
			while (ft_memchr(" \t\r\v\f\n", tmp[i]))
				i++;
			(*args)->next = ft_new_arg();
			(*args) = (*args)->next;
		}
	}
	free(tmp);
}

int	check_expand(char *line, t_list *list, t_arg **args, t_ne *l)
{
	int		j;
	char	*tmp;

	j = list->j;
	tmp = NULL;
	(*args)->exp = 1;
	if (list->args->arg)
		tmp = ft_last_arg(*list);
	if (!ft_strncmp(list->args->arg, "export", 6))
		j = check_export(line, list, args, l);
	else if (tmp && ft_memchr("<>", tmp[0]))
		j += ft_expand_nsplit(line + j + 1, *args, l->en, l);
	else if (j > 0)
	{
		j += ft_expand_nsplit(line + j + 1, *args, l->en, l);
		tmp = ft_strdup((*args)->arg);
		free((*args)->arg);
		(*args)->arg = NULL;
		add_args(tmp, args);
	}
	else
		j += ft_expand(line + j + 1, *args, l->en, l);
	while ((*args)->next)
		*args = (*args)->next;
	return (j);
}

int	duble_qoat(char *line, t_arg *args, t_ne *l, int *k)
{
	int	j;

	j = *k;
	while (line[j] && line[j] != '"')
	{
		args->co = 1;
		if (!l->l_here && line[j] == '$' && !ft_memchr(" =:\t\v\n\r\f|$\"><",
				line[j + 1]) && line)
		{
			if (*k < j)
				args->arg = ft_strnjoin(args->arg, line + *k, j - *k);
			j += ft_expand_nsplit(line + j + 1, args, l->en, l);
			*k = j + 1;
			if (line[j] == '"')
				return (j);
		}
		j++;
	}
	return (j);
}

int	check_qoat(char *line, t_arg *args, int j, t_ne *l)
{
	int	k;

	if (line[j] == '\'')
	{
		k = j + 1;
		skip_qoat(line, &j);
		args->arg = ft_strnjoin(args->arg, line + k, j - k);
		args->co = 1;
	}
	else if (line[j] == '"')
	{
		k = j + 1;
		j = duble_qoat(line, args, l, &k);
		if (!ft_memchr(" =:\t\v\n\r\f|$\"", line[j + 1]))
			l->l_here = 0;
		args->arg = ft_strnjoin(args->arg, line + k, j - k);
		args->co = 1;
	}
	return (j);
}
