/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:50:08 by sennakhl          #+#    #+#             */
/*   Updated: 2024/08/29 15:19:41 by sennakhl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_args(t_arg *args)
{
	t_arg	*head;

	while (args)
	{
		if (args->arg)
		{
			free(args->arg);
			args->arg = NULL;
		}
		head = args->next;
		free(args);
		args = NULL;
		if (!head)
			break ;
		args = head;
	}
}

void	ft_free_redi(t_redi *redi)
{
	t_redi	*head;

	while (redi)
	{
		if (redi->dir)
		{
			free(redi->dir);
			redi->dir = NULL;
		}
		if (redi->file)
		{
			free(redi->file);
			redi->file = NULL;
		}
		head = redi->next;
		free(redi);
		redi = head;
		if (!head)
			break ;
		head = head->next;
	}
	redi = NULL;
}

void	ft_free_list(t_list *list)
{
	t_list	*head;

	while (list)
	{
		if (list->token)
			free(list->token);
		if (list->args)
			ft_free_args(list->args);
		if (list->redi)
			ft_free_redi(list->redi);
		if (list->prt)
			ft_free_list(list->prt);
		head = list->next;
		free(list);
		list = head;
	}
	list = NULL;
}

int	check_free(char **line, t_ne *l, t_list *list)
{
	if (*line)
		free(*line);
	*line = NULL;
	if (!l->exi)
		return (1);
	ft_free_list(list);
	list = NULL;
	l->ili = 0;
	return (0);
}
