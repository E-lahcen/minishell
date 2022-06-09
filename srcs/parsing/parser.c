/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:41:46 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 15:14:47 by zwina            ###   ########.fr       */
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
	listline = parser_listline(line, env);
	if (error_unexpected(listline, line))
	{
		free_listline(listline);
		free(line);
		return (NULL);
	}
	set_pipestats(listline);
	free(line);
	return (listline);
}

void	set_pipestats(t_listline *listline)
{
	t_list	*lsttmp;

	lsttmp = listline->pipelines;
	while (lsttmp && lsttmp->next)
	{
		if (get_pipestat(lsttmp->content) == POR)
			((t_pipeline *)lsttmp->next->content)->pipestat = POR;
		else if (get_pipestat(lsttmp->content) == PAND)
			((t_pipeline *)lsttmp->next->content)->pipestat = PAND;
		else
			((t_pipeline *)lsttmp->content)->pipestat = 0;
		lsttmp = lsttmp->next;
	}
}

char	get_pipestat(t_pipeline *pipeline)
{
	t_list	*symbol;

	symbol = ft_lstlast(((t_cmdline *) \
			ft_lstlast(pipeline->cmdlines)->content)->words[1]);
	if (symbol->stat == S_OR)
		return (POR);
	else if (symbol->stat == S_AND)
		return (PAND);
	return (0);
}
