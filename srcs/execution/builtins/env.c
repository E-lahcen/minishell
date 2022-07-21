/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:15:56 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 20:32:43 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_cmdline *cmdline)
{
	size_t	i;
	char	**key_value;
	t_list	*env;

	i = 0;
	if (((t_cmd_infos *)cmdline->node->content)->cmd_args[1])
	{
		errors("env", "arguments are not supported", 0);
		errno = 1;
	}
	else
	{
		env = g_global.myenv;
		while (env)
		{
			key_value = env->content;
			if (key_value[1])
				print_env(key_value);
			env = env->next;
		}
	}
	g_global.exit = errno;
}

void	print_env(char **key_value)
{
	ft_putstr_fd(key_value[0], 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(key_value[1], 1);
}
