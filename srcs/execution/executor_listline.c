/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_listline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:27:51 by zwina             #+#    #+#             */
/*   Updated: 2022/06/25 17:21:32 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	executor_listline(t_cmdline *cmdline)
{
	t_list		*lsttmp;
	pid_t		pid;

	lsttmp = ((t_listline *)cmdline->node->content)->pipelines;
	while (lsttmp)
	{
		if (lsttmp->stat == PIPELINE)
		{
			sig_handler(IGNORE);
			pid = executor_pipeline(lsttmp->content);
			waitpid(pid, &g_global.exit, 0);
			if (g_global.exit == 2 || g_global.exit == 3)
				g_global.exit += 128;
			else
				g_global.exit = WEXITSTATUS(g_global.exit);
			while (wait(NULL) != -1)
				;
			sig_handler(HANDLER);
		}
		else if (check_symbol(lsttmp))
			lsttmp = lsttmp->next;
		lsttmp = lsttmp->next;
	}
	exit(g_global.exit);
}
