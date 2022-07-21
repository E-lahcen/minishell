/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:12:41 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 12:50:36 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*expand_dollars(t_list *elems)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (elems)
	{
		if ((elems->stat == DR) && ((char *)elems->content)[0] == '$')
		{
			lsttmp = elems->next;
			lsttmp2 = elems;
			elems = parser_dollar(elems);
			ft_lstdelone(lsttmp2, free);
			if (elems)
			{
				(ft_lstlast(elems))->next = lsttmp;
				break ;
			}
			elems = lsttmp;
		}
		else
			break ;
	}
	expand_dollars_loop(elems);
	return (elems);
}

void	expand_dollars_loop(t_list *elems)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (elems && elems->next)
	{
		if (elems->next->stat == DR && ((char *)elems->next->content)[0] == '$')
		{
			lsttmp = elems->next->next;
			lsttmp2 = elems->next;
			elems->next = parser_dollar(elems->next);
			ft_lstdelone(lsttmp2, free);
			if (elems->next)
				(ft_lstlast(elems->next))->next = lsttmp;
			else
				elems->next = lsttmp;
		}
		else
			elems = elems->next;
	}
}

t_list	*parser_dollar(t_list *node)
{
	t_list	*minielems;
	size_t	i;
	char	pos;

	expand(node);
	minielems = NULL;
	if (node->content == NULL)
		return (minielems);
	i = 0;
	pos = 0;
	while (((char *)node->content)[i])
	{
		if (((char *)node->content)[i] == ' ')
			i++;
		else
		{
			if (pos == 0)
				pos = F_NODE;
			else if (pos == F_NODE)
				pos = L_NODE;
			i = get_node(node->content, i, &minielems, pos);
		}
	}
	return (minielems);
}

size_t	get_node(char *str, size_t start, t_list **minielems, char pos)
{
	size_t	i;

	i = start;
	while (str[i] && str[i] != ' ')
		i++;
	ft_lstadd_back(minielems, \
		ft_lstnew(ft_substr(str, start, i - start), pos | DR));
	return (i);
}
