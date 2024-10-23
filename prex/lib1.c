/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckhater <ckhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:50:47 by ckhater           #+#    #+#             */
/*   Updated: 2024/08/29 18:02:02 by ckhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	helpato(int *i, unsigned long *n, long sign, char *str)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*n = (*n * 10) + (str[*i] - 48);
		if (sign == -1)
		{
			if (*n > 9223372036854775808UL)
				return (2);
		}
		else if (*n > LONG_MAX)
			return (2);
		*i = *i + 1;
	}
	return (0);
}

int	ft_atol(char *str, unsigned long *n)
{
	int		i;
	long	sign;

	sign = 1;
	*n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (helpato(&i, n, sign, str) == 2)
		return (2);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] != '\0')
		return (2);
	*n = *n * sign;
	return (0);
}

int	ft_lstsize(t_arg *lst)
{
	t_arg	*ar;
	int		cnt;

	ar = lst;
	cnt = 0;
	while (ar && ar->arg)
	{
		cnt++;
		ar = ar->next;
	}
	return (cnt);
}

int	ft_sizecm(t_arg *lst)
{
	t_arg	*ar;
	int		cnt;

	ar = lst;
	cnt = 0;
	while (ar)
	{
		if (ar->arg)
			cnt++;
		ar = ar->next;
	}
	return (cnt);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
