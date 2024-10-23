/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onecom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:11:17 by ckhater           #+#    #+#             */
/*   Updated: 2024/09/02 16:17:38 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	f_dupi(t_ne *l)
{
	if (!l->prenth)
	{
		l->stin = dup(0);
		l->stout = dup(1);
	}
}

void	f_dup(int *i, int s)
{
	dup2(*i, s);
	close(*i);
}

static void	f_dupc(t_ne *l)
{
	if (!l->prenth)
	{
		dup2(l->stin, STDIN_FILENO);
		close(l->stin);
		dup2(l->stout, STDOUT_FILENO);
		close(l->stout);
	}
}

static void	command(t_list *lst, t_ne *l)
{
	int	st;

	if (get_cmd(lst, l))
		return ;
	l->lpi = fork();
	if (l->lpi == -1)
	{
		perror("fork");
		l->status = 1;
	}
	if (l->lpi == 0)
	{
		child_sig(1);
		execve(l->cmpa, l->cm, l->env);
		perror("execve");
		exit(1);
	}
	waitpid(l->lpi, &st, 0);
	if (WIFEXITED(st))
		l->status = WEXITSTATUS(st);
	check_sig(st, l);
}

void	onecmd(t_list *lst, t_ne *l)
{
	t_arg	*ar;

	ar = lst->args;
	f_dupi(l);
	if (redire(lst, l) == 1)
	{
		f_dupc(l);
		return ;
	}
	if (ar)
	{
		while (ar)
		{
			if (ar->arg)
			{
				if (ft_strncmp(ar->arg, "exit", 5) == 0)
					l->exi = 0;
				command(lst, l);
				ft_frecmd(l);
				break ;
			}
			ar = ar->next;
		}
	}
	f_dupc(l);
}
