/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:02 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 07:50:23 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipeline	*parser_pipeline(char *line, char **env)
{
	t_pipeline	*pipeline;
	size_t		i;
	char		*tmp;

	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	pipeline->cmdlines = NULL;
	tmp = line;
	line = ft_strtrim(line, " ");
	free(tmp);
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			i = pipeline_loop(line, i, &pipeline->cmdlines, env);
	}
	pipeline->n = ft_lstsize(pipeline->cmdlines);
	free(line);
	return (pipeline);
}

size_t	pipeline_loop(char *line, size_t i, t_list **pipeline, char **env)
{
	if (line[i] == '|')
		i = get_pipe(line, i, pipeline);
	else if (line[i] == '(')
		i = get_parenthesis_pipeline(line, i, pipeline, env);
	else
		i = get_pipeline(line, i, pipeline, env);
	return (i);
}

size_t	get_pipe(char *line, size_t start, t_list **listline)
{
	ft_lstadd_back(listline, ft_lstnew(ft_substr(line, start, 1), S_PIPE));
	return (start + 1);
}

size_t	get_parenthesis_pipeline(char *line, size_t start, t_list **list, \
	char **env)
{
	size_t	end;
	size_t	i;
	size_t	j;

	end = skip_parenthesis(line, start);
	i = end + 1;
	while (line[start] == '(' && line[end] == ')')
	{
		start++;
		end--;
	}
	j = start;
	while (j < end)
	{
		if (line[j] == '|' || line[j] == '&')
			break ;
		j++;
	}
	if (j == end)
		ft_lstadd_back(list, ft_lstnew(parser_cmdline(\
		ft_substr(line, start, end - start + 1), env), CMDLINE));
	else
		ft_lstadd_back(list, ft_lstnew(parser_listline(\
		ft_substr(line, start, end - start + 1), env), LISTLINE));
	return (i);
}

size_t	get_pipeline(char *line, size_t start, t_list **listline, char **env)
{
	size_t	i;

	i = start;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quotes(line, i);
		i++;
	}
	ft_lstadd_back(listline, \
	ft_lstnew(parser_cmdline(ft_substr(line, start, i - start), env), \
	CMDLINE));
	return (i);
}
