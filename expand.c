/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:46:41 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/02 18:30:38 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*args_from_exp(t_arg *args, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && ft_memchr(" \t\v\n\r\f", line[i]))
		i++;
	while (args->next)
		args = args->next;
	while (line[i])
	{
		j = i;
		while (line[j] && !ft_memchr(" \r\f\t\v\n", line[j]))
			j++;
		args->arg = ft_strnjoin(args->arg, line + i, j - i);
		args->arg = check_empty(args->arg);
		while (line[j] && ft_memchr(" \t\v\n\r\f", line[j]))
			j++;
		if (!line[j])
			break ;
		args->next = ft_new_arg();
		args = args->next;
		i = j;
	}
	args->arg = check_empty(args->arg);
	return (args);
}

int	expand_def(char *line, t_arg *args, t_ne *l)
{
	char	*tmp;
	char	*t;

	if (line[0] == '?')
	{
		t = ft_itoa(l->status);
		tmp = args->arg;
		args->arg = ft_strjoin(args->arg, t, 0);
		return (free(tmp), free(t), 1);
	}
	if (line[0] == '"' || line[0] == '\'')
	{
		args->arg = ft_strjoin(args->arg, NULL, 0);
		return (1);
	}
	if (line[0] == '_' && !ft_memchr(" \t\n\r\v\f", line[1]))
	{
		tmp = args->arg;
		args->arg = ft_strjoin(args->arg, l->larc, 0);
		return (free(tmp), 1);
	}
	return (0);
}

int	cond_expand(char *line, t_arg *args, t_ne *l)
{
	char	*tmp;

	if (ft_memchr("?\"'", line[0]))
		return (expand_def(line, args, l));
	if (line[0] == '_' && (ft_memchr(" \t\n\f\v\r\"'", line[1]) || !line[1]))
		return (expand_def(line, args, l));
	if (!ft_strncmp(line, "PWD", 3) && !check_char(line[3]))
	{
		tmp = args->arg;
		args->arg = ft_strjoin(args->arg, l->pwd + 4, 0);
		args->arg = check_empty(args->arg);
		return (free(tmp), 3);
	}
	if (l->oldpwd && !ft_strncmp(line, "OLDPWD", 6) && !check_char(line[6]))
	{
		tmp = args->arg;
		args->arg = ft_strjoin(args->arg, l->oldpwd + 7, 0);
		args->arg = check_empty(args->arg);
		return (free(tmp), 6);
	}
	return (0);
}

int	ft_expand(char *line, t_arg *args, t_arg *en, t_ne *l)
{
	int		i;
	char	*tmp;

	i = cond_expand(line, args, l);
	if (i)
		return (i);
	i += check_white(line + i);
	while (en)
	{
		tmp = en->arg;
		if (!ft_strncmp(line, tmp, i) && tmp[i] == '=')
		{
			args = args_from_exp(args, tmp + i + 1);
			return (i);
		}
		en = en->next;
	}
	if (!args->arg[0])
	{
		free(args->arg);
		args->arg = NULL;
	}
	return (i);
}

int	ft_expand_nsplit(char *line, t_arg *args, t_arg *en, t_ne *l)
{
	int		i;
	char	*tmp;

	i = cond_expand(line, args, l);
	if (i)
		return (i);
	i += check_white(line + i);
	while (en)
	{
		if (!ft_strncmp(line, en->arg, i) && en->arg[i] == '=')
		{
			tmp = args->arg;
			args->arg = ft_strjoin(args->arg, en->arg + i + 1, 0);
			return (free(tmp), i);
		}
		en = en->next;
	}
	if (args->arg && !args->arg[0])
	{
		free(args->arg);
		args->arg = NULL;
	}
	return (i);
}
