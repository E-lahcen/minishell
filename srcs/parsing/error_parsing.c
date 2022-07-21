/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:18:09 by zwina             #+#    #+#             */
/*   Updated: 2022/06/25 19:18:13 by zwina            ###   ########.fr       */
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

int	error_parenthesis(char *line)
{
	if (closed_parenthesis(line))
	{
		errors(NULL, ERR_PARTH_C, 0);
		return (1);
	}
	if (empty_parenthesis(line))
	{
		errors(NULL, ERR_PARTH_E, 0);
		return (1);
	}
	return (0);
}

int	closed_parenthesis(char *line)
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
			return (1);
		i++;
	}
	if (stat != 0)
		return (1);
	return (0);
}

int	empty_parenthesis(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
		{
			i++;
			while (line[i] != ')')
			{
				if (line[i] != ' ')
					break ;
				i++;
			}
			if (line[i] == ')')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
