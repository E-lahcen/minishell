/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_listline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:26 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 12:31:08 by zwina            ###   ########.fr       */
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
		i = listline_loop(line, i, &listline->pipelines, env);
	listline->n = ft_lstsize(listline->pipelines);
	return (listline);
}

size_t	listline_loop(char *line, size_t i, t_list **listline, char **env)
{
	size_t	start;
	char	*str;
	char	q_type;

	start = i;
	while (line[i] && \
		!(line[i] == '|' && line[i + 1] == '|') && \
		line[i] != '&')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q_type = line[i++];
			while (line[i] != q_type)
				i++;
		}
		i++;
	}
	while (line[i] == ' ' || line[i] == '|' || line[i] == '&')
		i++;
	str = ft_substr(line, start, i - start);
	ft_lstadd_back(listline, ft_lstnew(parser_pipeline(str, env), 0));
	return (i);
}
