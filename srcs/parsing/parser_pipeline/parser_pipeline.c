/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:35:02 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 12:31:05 by zwina            ###   ########.fr       */
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
		i = pipeline_loop(line, i, &pipeline->cmdlines, env);
	pipeline->n = ft_lstsize(pipeline->cmdlines);
	free(line);
	return (pipeline);
}

size_t	pipeline_loop(char *line, size_t i, t_list **pipeline, char **env)
{
	size_t	start;
	char	*str;
	char	q_type;

	start = i;
	while (line[i] && line[i] != '|' && line[i] != '&')
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
	ft_lstadd_back(pipeline, ft_lstnew(parser_cmdline(str, env), 0));
	return (i);
}
