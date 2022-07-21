/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:39:52 by zwina             #+#    #+#             */
/*   Updated: 2022/07/21 13:22:35 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cmdline(t_cmdline *cmdline)
{
	cmdline->node = NULL;
	cmdline->words = NULL;
	cmdline->redirections = 0;
	cmdline->n_heredoc = 0;
	cmdline->o_a_i_h[0] = -1337;
	cmdline->o_a_i_h[1] = -1337;
	cmdline->o_a_i_h[2] = -1337;
	cmdline->o_a_i_h[3] = -1337;
}

void	fill_cmd_args(t_cmd_infos *cmd_infos, t_list *args)
{
	int	len;
	int	i;

	len = ft_lstsize(args) + 1;
	cmd_infos->cmd_args = (char **)malloc(sizeof(char *) * len);
	i = 0;
	while (args)
	{
		cmd_infos->cmd_args[i++] = ft_strdup(args->content);
		args = args->next;
	}
	cmd_infos->cmd_args[i] = NULL;
}

void	fill_cmd_path(t_cmd_infos *cmd_infos)
{
	char	**paths;
	size_t	i;

	if (!cmd_infos->cmd_args[0] || !cmd_infos->cmd_args[0][0] || \
	ft_strchr(cmd_infos->cmd_args[0], '/') || cmd_infos->cmd_args[0][0] == '.')
	{
		cmd_infos->cmd_path = ft_strdup(cmd_infos->cmd_args[0]);
		return ;
	}
	paths = get_paths();
	i = 0;
	while (paths[i])
	{
		cmd_infos->cmd_path = ft_strjoin(paths[i], cmd_infos->cmd_args[0]);
		if (!access(cmd_infos->cmd_path, X_OK))
			break ;
		free(cmd_infos->cmd_path);
		i++;
	}
	if (!paths[i])
		cmd_infos->cmd_path = ft_strdup(cmd_infos->cmd_args[0]);
	free_paths(paths);
}

size_t	set_parenthesis_limits(char *line, size_t *start, size_t *end)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = *end + 1;
	while (line[*start] == '(' && line[*end] == ')')
	{
		j = *start;
		count = 0;
		while (1)
		{
			if (line[j] == '(')
				count++;
			else if (line[j] == ')')
				count--;
			if (count == 0)
				break ;
			j++;
		}
		if (!move_start_end(j, start, end))
			break ;
	}
	return (i);
}

int	move_start_end(size_t j, size_t *start, size_t *end)
{
	if (j == *end)
	{
		(*start)++;
		(*end)--;
		return (1);
	}
	return (0);
}
