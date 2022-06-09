/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:15:33 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 15:30:08 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_quotes(char *line)
{
	char	q;
	size_t	i;

	q = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (q == 0)
				q = line[i];
			else if (q == line[i])
				q = 0;
		}
		i++;
	}
	if (q != 0)
	{
		errors(NULL, ERR_QUOTES, 0);
		return (1);
	}
	return (0);
}

int	error_parenthesis(char *line)
{
	size_t	i;
	int		stat;

	i = 0;
	stat = 0;
	while (line[i])
	{
		if (line[i] == '(')
			stat++;
		else if (line[i] == ')')
			stat--;
		if (stat < 0)
		{
			errors(NULL, ERR_PARTH, 0);
			return (1);
		}
		i++;
	}
	if (stat != 0)
	{
		errors(NULL, ERR_PARTH, 0);
		return (1);
	}
	return (0);
}

int	error_incomplete(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '&')
		{
			i++;
			if (line[i] != '&')
			{
				errors("&", ERR_INCP, 0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	error_unexpected(t_listline *listline, char *line)
{
	size_t	len;

	if (line[0] == '|' || line[0] == '&')
	{
		errors(\
		((t_cmdline *)((t_pipeline *) \
		listline->pipelines->content)->cmdlines->content)->words[1]->content, \
		ERR_UNEX, 0);
		return (1);
	}
	if (error_unexpected_loop(listline))
		return (1);
	len = ft_strlen(line);
	if (line[len - 1] == '|' || line[len - 1] == '&' || \
		line[len - 1] == '<' || line[len - 1] == '>')
	{
		errors("newline", ERR_UNEX, 0);
		return (1);
	}
	return (0);
}

int	error_unexpected_loop(t_listline *listline)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	lsttmp = listline->pipelines;
	while (lsttmp)
	{
		lsttmp2 = ((t_pipeline *)lsttmp->content)->cmdlines;
		while (lsttmp2)
		{
			if (set_heredoc(lsttmp2->content))
				return (1);
			lsttmp2 = lsttmp2->next;
		}
		lsttmp = lsttmp->next;
	}
	return (0);
}
