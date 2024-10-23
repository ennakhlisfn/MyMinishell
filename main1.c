/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:12:21 by sennakhl          #+#    #+#             */
/*   Updated: 2024/09/01 18:02:29 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	endm(char *tmp, char *line, t_list *list, t_ne *l)
{
	if (g_status == 130)
		l->status = 130;
	rl_clear_history();
	ft_free_list(list);
	if (tmp)
		free(tmp);
	if (line)
		free(line);
	f_freex(l);
	exit(l->status);
}

void	exfr(char *line, t_list *list, t_ne *l)
{
	if (g_status == 130)
		l->status = 130;
	rl_clear_history();
	ft_free_list(list);
	if (line)
		free(line);
	f_freex(l);
	exit(l->status);
}

void	handle_sig(int s)
{
	(void)s;
	if (g_status != 2)
		write(1, "\n", 1);
	g_status = 130;
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	parent_sig(int s)
{
	(void)s;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ge_line(char **line, t_ne *l, t_list *list)
{
	parent_sig(1);
	*line = readline("minishell$ ");
	if (g_status == 130)
		l->status = 130;
	if (!*line)
	{
		printf("exit\n");
		exfr(*line, list, l);
	}
	if (line && *line && *line[0])
		add_history(*line);
}
