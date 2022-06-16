/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:41:46 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 07:28:43 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_listline	*parser(char *line, char **env)
{
	t_listline	*listline;
	char		*tmp;

	tmp = line;
	line = ft_strtrim(line, " ");
	free(tmp);
	if (line[0] == '\0' || error_quotes(line) || \
		error_parenthesis(line) || error_incomplete(line))
	{
		free(line);
		return (NULL);
	}
	listline = parser_listline(ft_strdup(line), env);
	if (error_unexpected_listline(listline))
	{
		errors(NULL, ERR_UNEX, 0);
		free_listline(listline);
		free(line);
		return (NULL);
	}
	free(line);
	return (listline);
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

size_t	skip_quotes(char *line, size_t i)
{
	char	q;

	q = line[i];
	while (line[i] != q)
		i++;
	return (i);
}
