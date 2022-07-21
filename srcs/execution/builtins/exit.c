/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:13:44 by zwina             #+#    #+#             */
/*   Updated: 2022/07/20 11:10:07 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_exit(t_cmdline *cmdline)
{
	char *first_arg;
	int exit_status;

	first_arg = ((t_cmd_infos *)cmdline->node->content)->cmd_args[1];
	if (!first_arg)
		exiting(0);
	if (ft_isnumeric(first_arg))
	{
		if (((t_cmd_infos *)cmdline->node->content)->cmd_args[2])
		{
			g_global.exit = 1;
			errors("exit", "too many arguments", 0);
		}
		else
		{
			exit_status = ft_atoi(first_arg);
			exiting(exit_status);
		}
	}
	else
	{
		g_global.exit = 255;
		errors("exit", "numeric argument required", 0);
		exiting(255);
	}
}

void exiting(int status)
{
	ft_putendl_fd("exit", 1);
	g_global.exit = status;
	exit(status);
}

int ft_isnumeric(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
		{
			i++;
			continue;
		}
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int get_sign(char **first_arg)
{
	int sign;

	sign = 1;
	if ((*first_arg)[0] == '-' || (*first_arg)[0] == '+')
	{
		if ((*first_arg)[0] == '-')
			sign = -1;
		(*first_arg)++;
	}
	return (sign);
}
