/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:56:33 by sennakhl          #+#    #+#             */
/*   Updated: 2024/08/29 12:05:14 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_pa(char *line, int j, t_list *list, t_ne *l)
{
	int		k;
	t_arg	*arg;

	arg = list->args;
	while (line[j] && ft_memchr(" \t\v\n\r\f", line[j]))
		j++;
	while (arg->next)
		arg = arg->next;
	arg->next = ft_new_arg();
	arg = arg->next;
	if (!line[j] || line[j] == ')')
		return (j);
	if (line[j] == '|' || !ft_strncmp(line + j, "&&", 2))
		return (j);
	k = fill_args(line + j, arg, list, l);
	if (k < 0)
		return (-1);
	return (j + k);
}

char	*ft_last_arg(t_list list)
{
	if (!list.args->next)
		return (NULL);
	while (list.args->next->next)
		list.args = list.args->next;
	return (list.args->arg);
}

t_arg	*ft_new_arg(void)
{
	t_arg	*new_arg;

	new_arg = (t_arg *)malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->arg = NULL;
	new_arg->co = 0;
	new_arg->exp = 0;
	new_arg->next = NULL;
	return (new_arg);
}

t_redi	*ft_new_redi(void)
{
	t_redi	*new_redi;

	new_redi = (t_redi *)malloc(sizeof(t_redi));
	if (!new_redi)
		return (NULL);
	new_redi->dir = NULL;
	new_redi->file = NULL;
	new_redi->co = 0;
	new_redi->exp = 0;
	new_redi->next = NULL;
	return (new_redi);
}

t_list	*ft_lstnew(void)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!(new_node))
		return (NULL);
	new_node->token = NULL;
	new_node->args = ft_new_arg();
	new_node->redi = NULL;
	new_node->n_redi = 0;
	new_node->i = 0;
	new_node->j = 0;
	new_node->her = 0;
	new_node->prt = NULL;
	new_node->next = NULL;
	return (new_node);
}
