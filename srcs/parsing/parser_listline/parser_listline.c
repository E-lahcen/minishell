/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_listline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:26 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 09:16:16 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_listline	*parser_listline(char *line, char **env)
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
			i = listline_loop(line, i, &listline->pipelines, env);
	}
	listline->n = ft_lstsize(listline->pipelines);
	free(line);
	return (listline);
}

size_t	listline_loop(char *line, size_t i, t_list **listline, char **env)
{
	if ((line[i] == '&' && line[i + 1] == '&' ) || \
		(line[i] == '|' && line[i + 1] == '|'))
		i = get_symbols(line, i, listline);
	else if (line[i] == '(')
		i = get_parenthesis_listline(line, i, listline, env);
	else
		i = get_listline(line, i, listline, env);
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

size_t	get_parenthesis_listline(char *line, size_t start, t_list **list, \
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
		ft_lstadd_back(list, ft_lstnew(parser_pipeline(\
		ft_substr(line, start, end - start + 1), env), PIPELINE));
	else
		ft_lstadd_back(list, ft_lstnew(parser_listline(\
		ft_substr(line, start, end - start + 1), env), LISTLINE));
	return (i);
}

size_t	get_listline(char *line, size_t start, t_list **listline, char **env)
{
	size_t	i;

	i = start;
	while (line[i] && \
		!(line[i] == '&' && line[i + 1] == '&') && \
		!(line[i] == '|' && line[i + 1] == '|'))
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = skip_quotes(line, i);
		if (line[i] == '(')
			i = skip_parenthesis(line, i);
		i++;
	}
	ft_lstadd_back(listline, \
	ft_lstnew(parser_pipeline(ft_substr(line, start, i - start), env), \
	PIPELINE));
	return (i);
}
