/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:02:55 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/03 11:29:40 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	f_dupot(t_ne *l)
{
	if (!l->to)
	{
		close(l->nfd[0]);
		dup2(l->nfd[1], STDOUT_FILENO);
		close(l->nfd[1]);
	}
}

static void	f_dupin(t_ne *l)
{
	if (l->p)
	{
		close(l->ofd[1]);
		dup2(l->ofd[0], STDIN_FILENO);
		close(l->ofd[0]);
	}
}

void	excmd(t_list *lst, t_ne *l)
{
	if (get_cmd(lst, l))
	{
		f_freex(l);
		exit(l->status);
	}
	execve(l->cmpa, l->cm, l->env);
	perror("execve");
	f_freex(l);
	exit(1);
}

void	execcmd(t_list *lst, t_ne *l)
{
	l->lpi = fork();
	if (l->lpi == -1)
	{
		l->status = 1;
		return (perror("fork"));
	}
	if (l->lpi == 0)
	{
		child_sig(1);
		f_dupin(l);
		f_dupot(l);
		if (redire(lst, l))
			exit(l->status);
		if (lst->prt)
			subpipe(lst->prt, l);
		excmd(lst, l);
		f_freex(l);
		ft_free_list(lst);
		exit(l->status);
	}
}

void	fpipe(t_list *lst, t_ne *l)
{
	if (l->p || l->prenth == 1)
	{
		l->ofd[0] = l->nfd[0];
		l->ofd[1] = l->nfd[1];
	}
	if (ft_strcmp(lst->token, "|"))
		l->to = 1;
	if (!ft_strcmp(lst->token, "|"))
	{
		if (pipe(l->nfd) < 0)
		{
			perror("pipe");
			l->status = 1;
			return ;
		}
	}
	execcmd(lst, l);
}
