/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:11:27 by zwina             #+#    #+#             */
/*   Updated: 2022/06/15 13:20:11 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exit;

int	main(int ac, char **av, char **env)
{
	t_listline	*listline;
	char		*line;

	(void)av;
	if (ac != 1)
	{
		errors(NULL, "Arguments are not supported.", 0);
		return (1);
	}
	sighandler();
	while (1)
	{
		line = readline("\e[38;5;118mminishell$\e[0m ");
		if (!line)
			ctrl_d_func();
		if (line[0])
			add_history(line);
		listline = parser(line, env);
		print_listline(listline, 0);
		executor(listline);
	}
	return (0);
}
