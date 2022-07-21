/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:02 by zwina             #+#    #+#             */
/*   Updated: 2022/07/20 10:11:44 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipeline *parser_pipeline(char *line)
{
	t_pipeline *pipeline;
	size_t i;

	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	pipeline->cmdlines = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			i = pipeline_loop(line, i, &pipeline->cmdlines);
	}
	pipeline->n = ft_lstsize(pipeline->cmdlines);
	free(line);
	return (pipeline);
}

size_t pipeline_loop(char *line, size_t i, t_list **pipeline)
{
	if (line[i] == '|')
		i = get_pipe(line, i, pipeline);
	else
		i = get_cmdline(line, i, pipeline);
	return (i);
}

size_t get_pipe(char *line, size_t start, t_list **listline)
{
	ft_lstadd_back(listline, ft_lstnew(ft_substr(line, start, 1), S_PIPE));
	return (start + 1);
}

size_t get_cmdline(char *line, size_t start, t_list **listline)
{
	size_t i;

	i = start;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quotes(line, i);
		if (line[i] == '(')
			i = skip_parenthesis(line, i);
		i++;
	}
	ft_lstadd_back(listline,
				   ft_lstnew(parser_cmdline(ft_substr(line, start, i - start)),
							 CMDLINE));
	return (i);
}

size_t skip_quotes(char *line, size_t i)
{
	char q;

	q = line[i++];
	while (line[i] != q)
		i++;
	return (i);
}
