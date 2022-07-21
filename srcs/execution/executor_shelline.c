/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_shelline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:59:53 by lelhlami          #+#    #+#             */
/*   Updated: 2022/07/20 12:53:50 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int check_symbol(t_list *node)
{
	if (node->stat == S_AND && g_global.exit)
		return (1);
	else if (node->stat == S_OR && g_global.exit == 0)
		return (1);
	return (0);
}

void executor_shelline(t_listline *shelline)
{
	t_list *lsttmp;
	pid_t pid;

	lsttmp = shelline->pipelines;
	while (lsttmp)
	{
		if (lsttmp->stat == PIPELINE)
		{
			sig_handler(IGNORE);
			pid = executor_pipeline(lsttmp->content);
			waitpid(pid, &g_global.exit, 0);
			if (g_global.exit == 2 || g_global.exit == 3)
				g_global.exit += 128;
			else if (g_global.exit != 1)
				g_global.exit = WEXITSTATUS(g_global.exit);
			while (wait(NULL) != -1)
				;
			sig_handler(HANDLER);
		}
		else if (check_symbol(lsttmp))
			lsttmp = lsttmp->next;
		lsttmp = lsttmp->next;
	}
}
