/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:31:22 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/03 11:17:39 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dd(char *a, t_ne *l)
{
	if (!ft_strcmp(a, "."))
	{
		wrerr(a, "filename  argument required", 2, l);
		return (1);
	}
	else if (!ft_strcmp(a, ".."))
	{
		wrerr(a, "command not found", 127, l);
		return (1);
	}
	if (isdire(l->cm[0]) && ft_memchr(a, '/'))
	{
		wrerr(l->cm[0], "Is a directory", 126, l);
		return (1);
	}
	return (0);
}

int	check_er(char *path, char *a, t_ne *l)
{
	if (check_dd(a, l))
		return (free(path), 1);
	else if (!ft_strncmp(a, "./", 2))
	{
		if (access(l->cm[0], F_OK))
		{
			wrerr(l->cm[0], "No such file or directory", 127, l);
			return (free(path), 1);
		}
		else if (access(l->cm[0], X_OK))
		{
			wrerr(l->cm[0], "Permission denied", 126, l);
			return (free(path), 1);
		}
		else if (!access(l->cm[0], F_OK | X_OK))
			return (l->cmpa = ft_strdup(l->cm[0]), free(path), 0);
	}
	else if (ft_memchr(a, '/'))
		return (checksla(path, l));
	return (2);
}

int	ccmd(char *path, t_ne *l, char **spath, char *temp)
{
	if (ft_strnstr(path, "::", ft_strlen(path)))
	{
		if (!access(l->cm[0], F_OK | X_OK) && !isdire(l->cm[0]))
		{
			l->cmpa = ft_strdup(l->cm[0]);
			return (ft_frestr(spath), free(path), free(temp), 0);
		}
		if (access(l->cm[0], X_OK))
			return (ft_frestr(spath), free(path), free(temp), wrerr(l->cm[0],
					"Permission denied", 126, l), 1);
	}
	if (!l->cmpa)
		return (ft_frestr(spath), free(path), free(temp), wrerr(l->cm[0],
				"command not found", 127, l), 1);
	if (access(l->cmpa, X_OK) == -1)
		return (ft_frestr(spath), free(path), free(temp), wrerr(l->cm[0],
				"Permission denied", 126, l), 1);
	return (ft_frestr(spath), free(path), free(temp), 0);
}

int	cmd_check(char *path, t_ne *l)
{
	char	**spath;
	char	*temp;
	int		j;

	j = -1;
	spath = ft_split(path, ':');
	temp = ft_strjoin("/", l->cm[0], 0);
	while (spath[++j])
	{
		l->cmpa = ft_strjoin(spath[j], temp, 0);
		if (!access(l->cmpa, F_OK) && *l->cm[0])
			return (free(temp), free(path), ft_frestr(spath), 0);
		else
		{
			free(l->cmpa);
			l->cmpa = NULL;
		}
	}
	return (ccmd(path, l, spath, temp));
}

int	get_cmd(t_list *lst, t_ne *l)
{
	char	*path;
	int		j;

	j = 0;
	if (ft_sizecm(lst->args))
	{
		path = ft_getenv("PATH=", l);
		filcmd(lst, l);
		if (!check_builtin(l))
			return (free(path), 1);
		f_varscore(l);
		if (!path || !*path)
			return (nopa(lst->args->arg, path, l));
		j = check_er(path, lst->args->arg, l);
		if (j != 2)
			return (j);
		return (cmd_check(path, l));
	}
	return (1);
}
