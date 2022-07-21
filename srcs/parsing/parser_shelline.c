/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shelline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:41:46 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 14:13:57 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_listline	*parser_shelline(char *line)
{
	t_listline	*shelline;

	if (errors_before_parsing(line))
	{
		g_global.exit = 258;
		free(line);
		return (NULL);
	}
	shelline = parser_listline(ft_strdup(line));
	if (errors_after_parsing(shelline))
	{
		free_listline(shelline);
		free(line);
		return (NULL);
	}
	free(line);
	return (shelline);
}

int	errors_before_parsing(char *line)
{
	if (error_quotes(line) || error_incomplete(line) || error_parenthesis(line))
		return (1);
	return (0);
}

int	errors_after_parsing(t_listline *shelline)
{
	t_list	*unexpected_node;
	int		fd;

	unexpected_node = error_unexpected_listline(shelline);
	if (unexpected_node)
		errors(unexpected_node->content, ERR_UNEX, 0);
	fd = dup(0);
	signal(SIGINT, ctrl_c_heredoc);
	set_heredocs_listline(shelline);
	dup(fd);
	close(fd);
	signal(SIGINT, ctrl_c);
	if (unexpected_node)
	{
		g_global.exit = 258;
		return (1);
	}
	if (g_global.heredoc_ctrlc)
	{
		g_global.exit = 1;
		return (1);
	}
	return (0);
}
