/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:29:53 by zwina             #+#    #+#             */
/*   Updated: 2022/07/20 14:18:03 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t executor_pipeline(t_pipeline *pipeline)
{
	pid_t pid;
	int fd[2];
	int default_in;

	pid = 0;
	if (ft_lstsize(pipeline->cmdlines) == 1 && ((t_cmdline *)pipeline->cmdlines->content)->node->stat == CMDLINE && is_builtins(((t_cmd_infos *)((t_cmdline *)pipeline->cmdlines->content)->node->content)->cmd_args[0]))
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
		executor_cmdline(pipeline->cmdlines->content, 1);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		default_in = dup(0);
		pid = executor_pipeline_loop(pipeline->cmdlines, fd);
		dup2(default_in, 0);
		close(default_in);
	}
	return (pid);
}

pid_t executor_pipeline_loop(t_list *cmdlines, int *pipe_fd)
{
	pid_t pid;

	while (cmdlines)
	{
		if (cmdlines->stat == S_PIPE)
		{
			cmdlines = cmdlines->next;
			continue;
		}
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			sig_handler(DEFAULT);
			if (cmdlines->next)
				dup_close_pipe(pipe_fd, 1);
			executor_cmdline(cmdlines->content, 0);
			exit(g_global.exit);
		}
		dup_close_pipe(pipe_fd, 0);
		cmdlines = cmdlines->next;
	}
	return (pid);
}

void dup_close_pipe(int *pipe_fd, int standard)
{
	dup2(pipe_fd[standard], standard);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
