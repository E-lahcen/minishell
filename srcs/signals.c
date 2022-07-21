/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:57:03 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 14:13:35 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_global.heredoc_ctrlc = 1;
	g_global.heredoc_newl = 1;
	g_global.exit = 1;
	close(0);
	ft_putchar_fd('\n', 1);
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_global.heredoc_newl == 0)
		ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(char type)
{
	if (type == HANDLER)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
