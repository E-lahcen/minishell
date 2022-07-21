/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_listline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:26 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 12:47:51 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_listline	*parser_listline(char *line)
{
	t_listline	*listline;
	size_t		i;

	listline = (t_listline *)malloc(sizeof(t_listline));
	listline->pipelines = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
			i = listline_loop(line, i, &listline->pipelines);
	}
	listline->n = ft_lstsize(listline->pipelines);
	free(line);
	return (listline);
}

size_t	listline_loop(char *line, size_t i, t_list **listline)
{
	if ((line[i] == '&' && line[i + 1] == '&' ) || \
		(line[i] == '|' && line[i + 1] == '|'))
		i = get_symbols(line, i, listline);
	else
		i = get_pipeline(line, i, listline);
	return (i);
}

size_t	get_symbols(char *line, size_t start, t_list **listline)
{
	if (line[start] == '&')
		ft_lstadd_back(listline, ft_lstnew(ft_substr(line, start, 2), S_AND));
	else if (line[start] == '|')
		ft_lstadd_back(listline, ft_lstnew(ft_substr(line, start, 2), S_OR));
	return (start + 2);
}

size_t	get_pipeline(char *line, size_t start, t_list **listline)
{
	size_t	i;

	i = start;
	while (line[i] && \
		!(line[i] == '&' && line[i + 1] == '&') && \
		!(line[i] == '|' && line[i + 1] == '|'))
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quotes(line, i);
		else if (line[i] == '(')
			i = skip_parenthesis(line, i);
		i++;
	}
	ft_lstadd_back(listline, \
	ft_lstnew(parser_pipeline(ft_substr(line, start, i - start)), \
	PIPELINE));
	return (i);
}

size_t	skip_parenthesis(char *line, size_t i)
{
	size_t	count;

	count = 1;
	i++;
	while (count)
	{
		if (line[i] == '(')
			count++;
		else if (line[i] == ')')
			count--;
		if (count)
			i++;
	}
	return (i);
}
