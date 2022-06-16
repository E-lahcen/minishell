/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:37:28 by zwina             #+#    #+#             */
/*   Updated: 2022/06/12 17:27:33 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	symbols_parenthesis(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
		{
			if (i > 0 && open_parenthesis(line, i))
				return (1);
		}
		else if (line[i] == ')')
		{
			if (close_parenthesis(line, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	open_parenthesis(char *line, size_t i)
{
	size_t	j;

	j = i - 1;
	while (line[j] == ' ' && j > 0)
		j--;
	if (line[j] != ' ' && line[j] != '|' && line[j] != '&' && line[j] != '(')
		return (1);
	j = i + 1;
	while (line[j] == ' ')
		j++;
	if (line[j] == '|' || line[j] == '&')
		return (1);
	return (0);
}

int	close_parenthesis(char *line, size_t i)
{
	size_t	j;

	j = i - 1;
	while (line[j] == ' ' && j > 0)
		j--;
	if (line[j] == '|' || line[j] == '&' || \
		line[j] == '>' || line[j] == '<')
		return (1);
	j = i + 1;
	while (line[j] == ' ')
		j++;
	if (line[j] != '\0' && line[j] != '|' && line[j] != '&' && line[j] != ')')
		return (1);
	return (0);
}
