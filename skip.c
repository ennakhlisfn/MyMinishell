/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:33:36 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 16:47:28 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	l_par(char *line)
{
	int	i;
	int	end;

	end = 0;
	i = 1;
	while (line[i])
	{
		if (!end && line[i] == ')')
			return (i);
		else if (line[i] == ')')
			end--;
		else if (line[i] == '(')
			end++;
		i++;
	}
	return (i);
}

int	first_skip(char *line, int *i, t_list *list, t_ne *l)
{
	int	k;

	while (line[*i] && ft_memchr(" \t\v\n\r\f", line[*i]))
		*i += 1;
	if (!line[*i] || line[*i] == ')')
		return (-2);
	if (line[*i] == '|' || !ft_strncmp(line + *i, "&&", 2))
		return (-2);
	else if (line[*i] == '(')
	{
		k = parenthes(list, line + *i, l);
		if (k < 0)
			return (-1);
		*i += k;
	}
	return (0);
}

int	skip_parenthese(char *line, t_ne *l, int *j, int *s)
{
	int		i;
	int		k;
	char	*tmp;

	i = *j;
	while (line[i] && line[i] != ')')
	{
		skip_qoat(line, &i);
		if (i < 0)
			return (-1);
		i++;
		if (line[i] == '(')
		{
			tmp = ft_strdup(line + i);
			k = unclosed(tmp, l, s);
			free(tmp);
			if (!k)
				return (0);
			i += k;
		}
	}
	if (!line[i])
		return (-1);
	return (i);
}

int	skip(char *line, t_ne *l)
{
	int	i;

	i = 0;
	while (ft_memchr(" \t\v\r", line[i]))
		i++;
	if (line[i] == '|' || line[i] == '&')
		return (syntax_error(l) - 1);
	if (!line[i] || line[i] == '\n')
		return (-1);
	while (line[i] && !ft_memchr("|&><", line[i]))
	{
		if (line[i] == '\'' || line[i])
		{
			skip_qoat(line, &i);
			if (i < 0)
				return (-1);
		}
		i++;
	}
	return (i);
}

void	skip_qoat(char *line, int *j)
{
	int	i;
	int	k;

	i = *j;
	k = i;
	if (line[i] && (line[i] == '"' || line[i] == '\''))
	{
		i++;
		while (line[i] && line[i] != line[k])
			i++;
		if (!line[i])
		{
			*j = -1;
			return ;
		}
		*j = i;
	}
}
