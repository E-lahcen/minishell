/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:34:46 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 12:49:16 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmdline	*parser_cmdline(char *line)
{
	t_cmdline	*cmdline;

	cmdline = (t_cmdline *)malloc(sizeof(t_cmdline));
	init_cmdline(cmdline);
	if (line[0] == '(')
		parser_cmdline_with_parth(line, cmdline);
	else
		parser_cmdline_without_parth(line, cmdline);
	free(line);
	return (cmdline);
}

void	parser_cmdline_without_parth(char *line, t_cmdline *cmdline)
{
	cmdline->words = parser_word(line);
	set_stats(cmdline->words[1]);
	set_stats(cmdline->words[2]);
	cmdline->words[0] = expand_args(cmdline->words[0]);
	ft_lstadd_back(&cmdline->node, \
		ft_lstnew(malloc(sizeof(t_cmd_infos)), CMDLINE));
	fill_cmd_args(cmdline->node->content, cmdline->words[0]);
	fill_cmd_path(cmdline->node->content);
}

void	parser_cmdline_with_parth(char *line, t_cmdline *cmdline)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = skip_parenthesis(line, start);
	if (is_one_cmd(line, start, end))
	{
		line = remove_parenthesis(line);
		parser_cmdline_without_parth(line, cmdline);
		free(line);
	}
	else
	{
		i = set_parenthesis_limits(line, &start, &end);
		ft_lstadd_back(&cmdline->node, ft_lstnew(parser_listline(\
			ft_substr(line, start, end - start + 1)), LISTLINE));
		cmdline->words = parser_word(line + i);
		set_stats(cmdline->words[1]);
		set_stats(cmdline->words[2]);
	}
}

int	is_one_cmd(char *line, size_t start, size_t end)
{
	while (start < end)
	{
		if (line[start] == '|' || line[start] == '&')
			return (0);
		start++;
	}
	end++;
	while (line[end])
	{
		if (line[end] != ' ')
			return (0);
		end++;
	}
	return (1);
}

char	*remove_parenthesis(char *line)
{
	char	*new_line;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != '(' && line[i] != ')')
			size++;
		i++;
	}
	size++;
	new_line = (char *)malloc(sizeof(char) * size);
	i = 0;
	size = 0;
	while (line[i])
	{
		if (line[i] != '(' && line[i] != ')')
			new_line[size++] = line[i];
		i++;
	}
	new_line[size] = '\0';
	return (new_line);
}
