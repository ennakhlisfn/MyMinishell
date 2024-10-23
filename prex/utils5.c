/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:16:05 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/29 15:41:39 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checksla(char *path, t_ne *l)
{
	DIR	*d;

	d = opendir(l->cm[0]);
	if (d)
	{
		wrerr(l->cm[0], "Is a directory", 126, l);
		closedir(d);
		return (free(path), 1);
	}
	else
	{
		if (access(l->cm[0], F_OK))
		{
			wrerr(l->cm[0], "No such file or directory", 127, l);
			return (free(path), 1);
		}
		else if (access(l->cm[0], X_OK))
			return (free(path), wrerr(l->cm[0], "Permission denied", 126, l),
				1);
		else if (!access(l->cm[0], F_OK | X_OK))
			return (l->cmpa = ft_strdup(l->cm[0]), free(path), 0);
	}
	return (0);
}

void	child_sig(int s)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	s = 0;
}

void	check_sig(int st, t_ne *l)
{
	if (WIFSIGNALED(st))
	{
		l->status = WTERMSIG(st) + 128;
		if (l->status == 131)
			write(2, "Quit (core dumped)", 19);
		write(2, "\n", 1);
	}
}

int	checkdir(t_ne *l, t_redi *head, int *err)
{
	DIR		*d;
	char	*file;

	if (!*err)
	{
		file = head->file;
		if (checkam(head, l, err))
			return (1);
		d = opendir(file);
		if (d)
		{
			wrerr(file, "Is a directory", 1, l);
			closedir(d);
			l->inf = -2;
			l->outf = -2;
			return (1);
		}
	}
	return (0);
}

void	checkpwd(char *h, t_ne *l)
{
	if (!ft_strcmp(h, "PWD"))
	{
		ft_free(l->pwd);
		l->pwd = ft_strdup("PWD=");
	}
	else if (!ft_strcmp(h, "OLDPWD"))
	{
		ft_free(l->oldpwd);
		l->oldpwd = ft_strdup("OLDPWD=");
	}
}
