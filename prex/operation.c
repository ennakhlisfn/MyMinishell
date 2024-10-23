/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:44:29 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 16:38:49 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_ne *l)
{
	if (ft_strncmp(l->cm[0], "exit", 5) == 0)
		return (f_exit(l), 0);
	else if (ft_strncmp(l->cm[0], "echo", 5) == 0)
		return (f_echo(l), 0);
	else if (ft_strncmp(l->cm[0], "cd", 3) == 0)
		return (f_cd(l), 0);
	else if (ft_strncmp(l->cm[0], "pwd", 4) == 0)
		return (f_pwd(l), 0);
	else if (ft_strncmp(l->cm[0], "env", 4) == 0)
		return (f_env(l), 0);
	else if (ft_strncmp(l->cm[0], "export", 7) == 0)
		return (f_expo(l), 0);
	else if (ft_strncmp(l->cm[0], "unset", 6) == 0)
		return (f_unse(l), 0);
	return (1);
}

int	oor(t_list *lst, t_ne *l)
{
	if (!l->to)
	{
		if (lst->prt)
		{
			subshel(lst, l);
			l->to = 0;
		}
		else
			onecmd(lst, l);
	}
	else
		l->to = 0;
	if (l->status == 0 || l->status == 130)
		return (1);
	return (0);
}

int	oand(t_list *lst, t_ne *l)
{
	if (!l->to)
	{
		if (lst->prt)
		{
			subshel(lst, l);
			l->to = 0;
		}
		else
			onecmd(lst, l);
	}
	else
		l->to = 0;
	if (l->status != 0)
		return (1);
	return (0);
}

int	nopa(char *a, char *path, t_ne *l)
{
	DIR	*d;

	d = opendir(l->cm[0]);
	if (d)
	{
		wrerr(l->cm[0], "Is a directory", 126, l);
		closedir(d);
	}
	else if (!access(a, F_OK | X_OK))
	{
		l->cmpa = ft_strdup(a);
		free(path);
		return (0);
	}
	else if (access(a, F_OK))
		wrerr(a, "NO such file or directory", 127, l);
	else
		wrerr(a, "Permission denied", 126, l);
	free(path);
	return (1);
}

void	filcmd(t_list *lst, t_ne *l)
{
	t_arg	*head;
	int		j;

	j = 0;
	head = lst->args;
	l->cm = fcreate(ft_sizecm(head) + 1);
	while (head)
	{
		if (head->arg)
		{
			l->cm[j] = ft_strdup(head->arg);
			j++;
		}
		head = head->next;
	}
}
