/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:14:51 by zwina             #+#    #+#             */
/*   Updated: 2022/06/24 15:54:14 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_cmdline *cmdline)
{
	char	**args;
	size_t	i;
	size_t	new_line;

	args = ((t_cmd_infos *)cmdline->node->content)->cmd_args + 1;
	new_line = 1;
	i = skip_minus_n(args);
	if (i > 0)
		new_line = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line == 1)
		ft_putchar_fd('\n', 1);
	g_global.exit = errno;
}

size_t	skip_minus_n(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (!is_minus_n(args[i]))
			break ;
		i++;
	}
	return (i);
}

int	is_minus_n(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && arg[i] != '-')
			return (0);
		if (i > 0 && arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
