/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:13:33 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/03 11:16:53 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	doerr(char **f, int *err, int i, char *redir)
{
	*err = i;
	*f = ft_strdup(redir);
}

int	check_inf(char **f, int *err, t_redi *head, t_ne *l)
{
	if (!ft_strcmp(head->dir, "<"))
	{
		if (checkam(head, l, err))
			return (1);
		else if (access(head->file, F_OK) == -1 && !*err)
			doerr(f, err, 1, head->file);
		else if (access(head->file, R_OK) == -1 && !*err)
			doerr(f, err, 2, head->file);
		else if (!*err)
		{
			l->inf = open(head->file, O_RDONLY);
			f_dup(&l->inf, 0);
		}
	}
	else if (!ft_strcmp(head->dir, "<<"))
	{
		l->inf = open(head->file, O_RDONLY);
		if (l->inf == -1)
			return (wrerr(NULL, "Heredoc temporary file does not exist", 1, l),
				1);
		else if (!*err)
			f_dup(&l->inf, 0);
	}
	return (0);
}

int	check_out(char **f, int *err, t_redi *head, t_ne *l)
{
	if (checkdir(l, head, err))
		return (1);
	if (!*err)
	{
		if (!ft_strcmp(head->dir, ">"))
			l->outf = open(head->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (!ft_strcmp(head->dir, ">>"))
			l->outf = open(head->file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (l->outf == -1)
		{
			if (access(head->file, F_OK))
				doerr(f, err, 1, head->file);
			else
				doerr(f, err, 2, head->file);
		}
		else if (l->outf != -2)
			f_dup(&l->outf, 1);
	}
	return (0);
}

int	cherro(int err, char *f, t_ne *l)
{
	if (err == 1)
	{
		write(2, "minishell: ", 12);
		write(2, f, ft_strlen(f));
		write(2, " :No such file or directory\n", 29);
		free(f);
		l->status = 1;
		l->inf = -2;
		l->outf = -2;
		return (1);
	}
	else if (err == 2)
	{
		write(2, "minishell: ", 12);
		write(2, f, ft_strlen(f));
		write(2, " :Permission denied\n", 21);
		free(f);
		l->status = 1;
		l->inf = -2;
		l->outf = -2;
		return (1);
	}
	return (0);
}

int	redire(t_list *lst, t_ne *l)
{
	t_redi	*head;
	char	*f;
	int		err;

	l->inf = -2;
	l->outf = -2;
	if (lst->redi)
	{
		l->status = 0;
		f = NULL;
		err = 0;
		head = lst->redi;
		while (head)
		{
			if (check_inf(&f, &err, head, l))
				return (1);
			if (check_out(&f, &err, head, l))
				return (1);
			head = head->next;
		}
		if (cherro(err, f, l))
			return (1);
	}
	return (0);
}
