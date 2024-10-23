/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fexec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 08:20:43 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 12:50:22 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	subshel(t_list *lst, t_ne *l)
{
	pid_t	pi;
	int		st;

	pi = fork();
	if (pi == -1)
		return (wrerr(NULL, NULL, 1, l), perror("fork"));
	if (pi == 0)
	{
		if (redire(lst, l))
			exit(l->status);
		l->prenth = 1;
		ftexec(lst->prt, l);
		l->prenth = 0;
		f_freex(l);
		ft_frestr(l->buf);
		ft_free_list(lst->prt);
		exit(l->status);
	}
	waitpid(pi, &st, 0);
	if (WIFEXITED(st))
		l->status = WEXITSTATUS(st);
	check_sig(st, l);
}

int	checkop(t_list *lst, t_ne *l)
{
	if (!ft_strcmp(lst->token, "||"))
	{
		if (oor(lst, l))
			return (1);
	}
	else if (!ft_strcmp(lst->token, "&&"))
	{
		if (oand(lst, l))
			return (1);
	}
	else if (!l->to && lst->prt)
		subshel(lst, l);
	else if (!l->to)
		onecmd(lst, l);
	return (0);
}

void	fwait(t_ne *l)
{
	pid_t	w;
	int		st;

	if (l->lpi)
	{
		while (1)
		{
			g_status = 2;
			w = wait(&st);
			if (w == -1)
				break ;
			if (w == l->lpi)
			{
				if (WIFEXITED(st))
				{
					l->status = WEXITSTATUS(st);
					l->lpi = 0;
				}
				check_sig(st, l);
			}
		}
	}
}

void	ftexec(t_list *lt, t_ne *l)
{
	t_list	*lst;

	lst = lt;
	while (lst)
	{
		if (!ft_strcmp(lst->token, "|"))
		{
			fpipe(lst, l);
			while (lst && !ft_strcmp(lst->token, "|"))
			{
				l->p++;
				lst = lst->next;
				fpipe(lst, l);
				close(l->ofd[0]);
				close(l->ofd[1]);
			}
		}
		fwait(l);
		if (!lst)
			break ;
		if (checkop(lst, l))
			return ;
		lst = lst->next;
	}
}
