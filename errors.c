/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennakhl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:19:46 by sennakhl          #+#    #+#             */
/*   Updated: 2024/08/29 12:48:49 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_ne *l)
{
	l->status = 2;
	write(2, "syntax error\n", 13);
	return (0);
}

int	synt_prt(char *line)
{
	int	i;

	i = 0;
	while (ft_memchr(" \n\r\f\t\v", line[i]))
		i++;
	if (!line[i] || line[i] == ')')
		return (1);
	return (0);
}

int	check_export(char *line, t_list *list, t_arg **args, t_ne *l)
{
	int	j;

	j = list->j;
	if (j > 1 && line[j - 1] == '=' && ft_strcmp((*args)->arg, "="))
		j += ft_expand_nsplit(line + j + 1, *args, l->en, l);
	else
		j += ft_expand(line + j + 1, *args, l->en, l);
	return (j);
}

void	realbuf(char *name, t_ne *l)
{
	char	**t;
	int		i;

	i = 0;
	if (name)
	{
		if (!l->buf)
		{
			l->buf = fcreate(2);
			l->buf[0] = ft_strdup(name);
		}
		else
		{
			t = fcreate(parlen(l->buf) + 2);
			while (l->buf[i])
			{
				t[i] = ft_strdup(l->buf[i]);
				i++;
			}
			t[i] = ft_strdup(name);
			ft_frestr(l->buf);
			l->buf = t;
		}
		l->he++;
	}
}
