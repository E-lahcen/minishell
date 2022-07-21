/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmdline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:28:23 by zwina             #+#    #+#             */
/*   Updated: 2022/07/20 14:18:20 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void executor_cmdline(t_cmdline *cmdline, char built)
{
	int rt;

	rt = set_files(cmdline);
	if (rt && built)
	{
		g_global.exit = errno;
		return;
	}
	else if (rt && !built)
		exit(errno);
	if (cmdline->redirections & RD_OUTPUT)
		dup2(cmdline->o_a_i_h[0], 1);
	if (cmdline->redirections & RD_APPEND)
		dup2(cmdline->o_a_i_h[1], 1);
	if (cmdline->redirections & RD_INPUT)
		dup2(cmdline->o_a_i_h[2], 0);
	if (cmdline->redirections & RD_HEREDOC)
		dup2(cmdline->o_a_i_h[3], 0);
	if (cmdline->node->stat == LISTLINE)
		executor_listline(cmdline);
	else
		execute(cmdline);
}

void execute(t_cmdline *cmdline)
{
	t_cmd_infos *cmd;

	cmd = cmdline->node->content;
	if (cmd->cmd_args[0] == NULL)
		exit(0);
	if (is_builtins(cmd->cmd_args[0]))
		execute_builtins(cmdline);
	else if (!ft_strchr(cmd->cmd_path, '/'))
	{
		errno = 127;
		errors(cmd->cmd_path, ERR_CMDNOTFOUND, 1);
	}
	else if (execve(cmd->cmd_path, cmd->cmd_args, convert_my_env(g_global.myenv)) == -1)
		execve_errors(cmd->cmd_path);
}

char **convert_my_env(t_list *my_env)
{
	char **new_env;
	char **key_value;
	char *tmp;
	char *str;
	size_t i;

	new_env = (char **)malloc(sizeof(char *) * (ft_lstsize(my_env) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (my_env)
	{
		key_value = my_env->content;
		if (key_value[1])
		{
			tmp = ft_strjoin(key_value[0], "=");
			str = ft_strjoin(tmp, key_value[1]);
			free(tmp);
			new_env[i] = str;
			i++;
		}
		my_env = my_env->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

int is_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) ||
		!ft_strncmp(cmd, "cd", 3) ||
		!ft_strncmp(cmd, "pwd", 4) ||
		!ft_strncmp(cmd, "export", 7) ||
		!ft_strncmp(cmd, "unset", 6) ||
		!ft_strncmp(cmd, "env", 4) ||
		!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void execute_builtins(t_cmdline *cmdline)
{
	errno = 0;
	if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
					"echo", 5))
		ft_echo(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "cd", 3))
		ft_cd(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "pwd", 4))
		ft_pwd(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "export", 7))
		ft_export(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "unset", 6))
		ft_unset(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "env", 4))
		ft_env(cmdline);
	else if (!ft_strncmp(((t_cmd_infos *)cmdline->node->content)->cmd_args[0],
						 "exit", 5))
		ft_exit(cmdline);
}

void execve_errors(char *cmd_path)
{
	if (!access(cmd_path, X_OK))
	{
		errno = 126;
		errors(cmd_path, ERR_ISDIR, 1);
	}
	else if (!access(cmd_path, F_OK))
	{
		errno = 126;
		errors(cmd_path, ERR_PERMISSION, 1);
	}
	else
	{
		errno = 127;
		errors(cmd_path, ERR_NOSUCHFILE, 1);
	}
}
