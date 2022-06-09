/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:39:52 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 12:35:46 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cmdline(t_cmdline *cmdline, char **env)
{
	cmdline->cmd_path = NULL;
	cmdline->cmd_args = NULL;
	cmdline->redirections = 0;
	cmdline->output = -1337;
	cmdline->append = -1337;
	cmdline->input = -1337;
	cmdline->heredoc = -1337;
	cmdline->env = env;
}

void	fill_cmdline(t_cmdline *cmdline)
{
	fill_cmd_args(cmdline, cmdline->words[0]);
	fill_cmd_path(cmdline);
}

void	fill_cmd_args(t_cmdline *cmdline, t_list *args)
{
	int		len;
	int		i;

	len = ft_lstsize(args) + 1;
	cmdline->cmd_args = (char **)malloc(sizeof(char *) * len);
	i = 0;
	while (args)
	{
		cmdline->cmd_args[i++] = ft_strdup(args->content);
		args = args->next;
	}
	cmdline->cmd_args[i] = NULL;
}

void	fill_cmd_path(t_cmdline *cmdline)
{
	char	**paths;
	size_t	i;

	paths = get_paths(cmdline->env);
	i = 0;
	while (paths[i])
	{
		cmdline->cmd_path = ft_strjoin(paths[i], cmdline->cmd_args[0]);
		if (!access(cmdline->cmd_path, X_OK))
			break ;
		free(cmdline->cmd_path);
		i++;
	}
	if (!paths[i])
		cmdline->cmd_path = ft_strdup(cmdline->cmd_args[0]);
	free_paths(paths);
}
