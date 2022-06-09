/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:15:45 by zwina             #+#    #+#             */
/*   Updated: 2022/06/05 18:02:49 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*expand_quotes(t_list *elems, char **env)
{
	t_list	*hold;

	hold = elems;
	while (elems)
	{
		if (elems->stat == DQU)
			elems = parser_double_quote(elems, env);
		elems = elems->next;
	}
	return (hold);
}

t_list	*parser_double_quote(t_list *node, char **env)
{
	t_list	*minielems;
	t_list	*lsttmp;
	size_t	i;

	minielems = NULL;
	i = 0;
	while (((char *)node->content)[i])
		i = get_minielems(node->content, i, &minielems);
	lsttmp = minielems;
	while (lsttmp)
	{
		if (lsttmp->stat == DR)
			expand(lsttmp, env);
		lsttmp = lsttmp->next;
	}
	relink_double_quote(minielems, node);
	return (node);
}

size_t	get_minielems(char *content, size_t i, t_list **minielems)
{
	if (content[i] == '$' && \
		ft_isdigit(content[i + 1]))
		i = i + 2;
	else if (content[i] == '$' && \
		ft_isvalidvar(content[i + 1]))
		i = get_dollar(content, i, minielems);
	else
		i = get_in_elem(content, i, minielems);
	return (i);
}
