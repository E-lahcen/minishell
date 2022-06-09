/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:11:27 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 15:04:44 by zwina            ###   ########.fr       */
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
		return (0);
	while (1)
	{
		line = readline("\e[38;5;118mminishell$\e[0m ");
		if (line == NULL)
			continue ;
		if (line[0])
			add_history(line);
		listline = parser(line, env);
		print_listline(listline);
		executor(listline);
	}
	return (0);
}
