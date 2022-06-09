/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:34:46 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 15:03:54 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmdline	*parser_cmdline(char *line, char **env)
{
	t_cmdline	*cmdline;
	char		*tmp;

	cmdline = (t_cmdline *)malloc(sizeof(t_cmdline));
	init_cmdline(cmdline, env);
	tmp = line;
	line = ft_strtrim(line, " ");
	free(tmp);
	cmdline->words = parser_word(line);
	set_stats(cmdline->words[1]);
	cmdline->words[0] = expand_args(cmdline->words[0], env);
	cmdline->words[1] = expand_args(cmdline->words[1], env);
	fill_cmdline(cmdline);
	free(line);
	return (cmdline);
}

void	free_all(t_cmdline *cmdline, t_list **words, char *line)
{
	free(line);
	if (cmdline)
	{
		free_paths(cmdline->cmd_args);
		free(cmdline->cmd_path);
		close(cmdline->output);
		close(cmdline->append);
		close(cmdline->input);
		close(cmdline->heredoc);
		free(cmdline);
	}
	ft_lstclear(&(words[0]), free);
	ft_lstclear(&(words[1]), free);
	free(words);
}
