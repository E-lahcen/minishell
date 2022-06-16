/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:57:03 by zwina             #+#    #+#             */
/*   Updated: 2022/06/15 13:35:33 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ctrl_c_func(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_back_slash(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_d_func(void)
{
	printf("exit\n");
	exit(0);
}

void	sighandler(void)
{
	signal(SIGINT, ctrl_c_func);
	signal(SIGQUIT, ctrl_back_slash);
}
