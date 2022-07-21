/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_relinking.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:38:16 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 15:12:55 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand(t_list *node)
{
	char	*tmp;

	if (((char *)node->content)[0] != '$')
		return ;
	if (((char *)node->content)[1] == '0')
	{
		tmp = node->content;
		node->content = ft_strdup("minishell");
		free(tmp);
	}
	else if (((char *)node->content)[1] == '?')
	{
		tmp = node->content;
		node->content = ft_itoa(g_global.exit);
		free(tmp);
	}
	else if (ft_isalpha(((char *)node->content)[1]))
	{
		tmp = node->content;
		node->content = ft_strdup(getmyenv(tmp + 1));
		free(tmp);
	}
}

void	relink_double_quote(t_list *minielems, t_list *node)
{
	t_list	*lsttmp;
	char	*new_content;
	char	*tmp;

	lsttmp = minielems;
	new_content = ft_strdup("");
	while (lsttmp)
	{
		if (lsttmp->content)
		{
			tmp = new_content;
			new_content = ft_strjoin(new_content, lsttmp->content);
			free(tmp);
		}
		lsttmp = lsttmp->next;
	}
	ft_lstclear(&minielems, free);
	tmp = node->content;
	node->content = new_content;
	free(tmp);
}

t_list	*relink_arg(t_list	*elems)
{
	t_list	*lsttmp;
	t_list	*hold;
	char	*tmp;

	hold = elems;
	while (elems && elems->next)
	{
		if (!((elems->stat & DR) && (elems->next->stat & DR)) || \
	((elems->stat & DR) && \
	(elems->next->stat & (DR + F_NODE)) == (DR + F_NODE)))
		{
			lsttmp = elems->next;
			tmp = elems->content;
			elems->content = ft_strjoin(elems->content, lsttmp->content);
			elems->next = lsttmp->next;
			elems->stat = lsttmp->stat;
			ft_lstdelone(lsttmp, free);
			free(tmp);
		}
		else
			elems = elems->next;
	}
	return (hold);
}
