/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:28:33 by zwina             #+#    #+#             */
/*   Updated: 2022/06/08 13:26:13 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_quote(char *str, size_t start, t_list **elem, uint16_t stat)
{
	size_t	i;
	char	q;

	q = 0;
	if (stat == SQU)
		q = '\'';
	else if (stat == DQU)
		q = '\"';
	i = ++start;
	while (str[i] != q)
		i++;
	ft_lstadd_back(elem, ft_lstnew(ft_substr(str, start, i - start), stat));
	return (i + 1);
}

size_t	get_dollar(char *str, size_t start, t_list **elem)
{
	size_t	i;

	i = start + 1;
	if (str[i] == '?' || str[i] == '0')
		i++;
	else
	{
		while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
			i++;
	}
	ft_lstadd_back(elem, ft_lstnew(ft_substr(str, start, i - start), DR));
	return (i);
}

size_t	get_out_elem(char *str, size_t start, t_list **elem)
{
	size_t	i;

	i = start;
	i++;
	while (str[i] && str[i] != '$' && \
			str[i] != '\'' && str[i] != '\"')
		i++;
	ft_lstadd_back(elem, ft_lstnew(ft_substr(str, start, i - start), 0));
	return (i);
}

size_t	get_in_elem(char *str, size_t start, t_list **elem)
{
	size_t	i;

	i = start;
	i++;
	while (str[i] && str[i] != '$')
		i++;
	ft_lstadd_back(elem, ft_lstnew(ft_substr(str, start, i - start), 0));
	return (i);
}

size_t	get_symbol(char *line, size_t start, t_list **words)
{
	size_t	i;

	i = start;
	if (line[i] == '|')
	{
		i++;
		if (line[i] == '|')
			i++;
	}
	else if (line[i] == '&')
		i += 2;
	ft_lstadd_back(words, \
		ft_lstnew(ft_substr(line, start, i - start), 0));
	return (i);
}
