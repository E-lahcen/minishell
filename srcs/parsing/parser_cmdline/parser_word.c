/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:06:10 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 12:21:35 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	**parser_word(char *line)
{
	t_list	**words;
	size_t	i;

	words = (t_list **)malloc(sizeof(t_list *) * 3);
	words[0] = NULL;
	words[1] = NULL;
	words[2] = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '>' || line[i] == '<')
			i = get_redirection(line, i, &(words[1]), &(words[2]));
		else
			i = get_arg(line, i, &(words[0]), &(words[2]));
	}
	words[0] = expand_astrisk(words[0]);
	words[1] = expand_astrisk(words[1]);
	return (words);
}

size_t	get_redirection(char *line, size_t start, t_list **reds, t_list **wrds)
{
	size_t	i;

	i = start;
	if (line[i] == '>')
	{
		i++;
		if (line[i] == '>')
			i++;
	}
	else if (line[i] == '<')
	{
		i++;
		if (line[i] == '<')
			i++;
	}
	ft_lstadd_back(reds, ft_lstnew(ft_substr(line, start, i - start), 0));
	ft_lstadd_back(wrds, ft_lstnew(ft_substr(line, start, i - start), 0));
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '<' && line[i] != '>')
		i = get_arg(line, i, reds, wrds);
	return (i);
}

size_t	get_arg(char *line, size_t start, t_list **args, t_list **wrds)
{
	size_t	i;
	char	q_d[2];

	q_d[0] = 0;
	q_d[1] = 0;
	i = start;
	while (line[i] != '\0' && line[i] != ' ' && \
			line[i] != '<' && line[i] != '>')
		i = set_q_d(line, i, q_d);
	ft_lstadd_back(args, \
		ft_lstnew(ft_substr(line, start, i - start), q_d[0] | q_d[1]));
	ft_lstadd_back(wrds, \
		ft_lstnew(ft_substr(line, start, i - start), 0));
	return (i);
}

size_t	set_q_d(char *line, size_t i, char *q_d)
{
	char	q_type;

	if (line[i] == '\'' || line[i] == '\"')
	{
		q_type = line[i++];
		while (line[i] != q_type)
			i++;
		if (q_type == '\'')
			q_d[0] = q_d[0] | SQU;
		else if (q_type == '\"')
			q_d[0] = q_d[0] | DQU;
	}
	else if (line[i] == '$')
		q_d[1] = DR;
	i++;
	return (i);
}
