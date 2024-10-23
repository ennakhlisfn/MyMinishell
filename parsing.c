/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:36:47 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 18:22:11 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(char *line, t_ne *l)
{
	int	i;

	i = 0;
	while (ft_memchr(" \t\v\r", line[i]))
		i++;
	if (!line[i])
		return (syntax_error(l));
	return (check_logic(line + i, l));
}

int	check_logic(char *line, t_ne *l)
{
	int	i;

	i = skip(line, l);
	if (i < 0)
		return (0);
	if (!line[i])
		return (1);
	if (ft_memchr("|&><", line[i]))
	{
		i++;
		if (!line[i])
			return (syntax_error(l));
		if (line[i] == line[i - 1])
			return (check_error(line + i + 1, l));
		return (check_error(line + i, l));
	}
	return (1);
}

int	unclosed(char *line, t_ne *l, int *j)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		skip_qoat(line, &i);
		if (i < 0)
			return (syntax_error(l));
		if (line[i] == ')' && *j == 0)
			return (syntax_error(l));
		if (line[i] == ')' && *j == 1)
			return (i);
		if (line[i] == '(')
		{
			*j = 1;
			i = skip_parenthese(line, l, &i, j);
			if (i < 0)
				return (syntax_error(l));
			if (!i)
				return (0);
		}
		i++;
	}
	return (i);
}

int	parsing(char *line, t_list *list, t_ne *l)
{
	int	tr;
	int	j;

	j = 0;
	tr = check_logic(line, l);
	if (tr)
		tr = unclosed(line, l, &j);
	if (tr)
		tr = fill_lst(line, list, l);
	return (tr);
}
