/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unexpected.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:34:06 by zwina             #+#    #+#             */
/*   Updated: 2022/07/22 12:23:59 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list *error_unexpected_listline(t_listline *listline)
{
	t_list *unexpected_node;
	t_list *lsttmp;
	size_t pattern;

	lsttmp = listline->pipelines;
	pattern = 1;
	while (lsttmp)
	{
		if ((lsttmp->stat == S_AND || lsttmp->stat == S_OR) &&
			(pattern % 2 == 1 || !lsttmp->next))
		{
			return (lsttmp);
		}
		unexpected_node = get_unexpected_node(lsttmp);
		if (unexpected_node)
			return (unexpected_node);
		lsttmp = lsttmp->next;
		pattern++;
	}
	return (NULL);
}

t_list *error_unexpected_pipeline(t_pipeline *pipeline)
{
	t_list *unexpected_node;
	t_list *lsttmp;
	size_t pattern;

	lsttmp = pipeline->cmdlines;
	pattern = 1;
	while (lsttmp)
	{
		if (lsttmp->stat == S_PIPE && (pattern % 2 == 1 || !lsttmp->next))
			return (lsttmp);
		unexpected_node = get_unexpected_node(lsttmp);
		if (unexpected_node)
			return (unexpected_node);
		lsttmp = lsttmp->next;
		pattern++;
	}
	return (NULL);
}

t_list *error_unexpected_cmdline(t_cmdline *cmdline)
{
	t_list *unexpected_node;

	if (cmdline->node->stat == CMDLINE)
	{
		unexpected_node = error_unexpected_reds(cmdline);
		if (unexpected_node)
			return (unexpected_node);
	}
	else if (cmdline->node->stat == LISTLINE)
	{
		unexpected_node = error_unexpected_listline(cmdline->node->content);
		if (unexpected_node)
			return (unexpected_node);
		unexpected_node = error_unexpected_reds(cmdline);
		if (unexpected_node)
			return (unexpected_node);
	}
	return (NULL);
}

t_list *error_unexpected_reds(t_cmdline *cmdline)
{
	t_list *wrds;

	wrds = cmdline->words[2];
	while (wrds)
	{
		if (((wrds->stat & S_RD) && (!wrds->next || (wrds->next->stat &
													 S_RD))) ||
			(cmdline->node->stat == LISTLINE && !(wrds->stat & (S_RD + RD))) ||
			(cmdline->node->stat == CMDLINE && ((char *)wrds->content)[0] == '('))
		{
			if (((char *)wrds->content)[0] == '(')
			{
				free(wrds->content);
				wrds->content = ft_strdup("(");
			}
			return (wrds);
		}
		if ((wrds->stat & S_HEREDOC) && (wrds->next->stat & RD_HEREDOC))
		{
			close(cmdline->o_a_i_h[3]);
			cmdline->n_heredoc++;
		}
		wrds = wrds->next;
	}
	return (NULL);
}

t_list *get_unexpected_node(t_list *node)
{
	if (node->stat == LISTLINE)
		return (error_unexpected_listline(node->content));
	else if (node->stat == PIPELINE)
		return (error_unexpected_pipeline(node->content));
	else if (node->stat == CMDLINE)
		return (error_unexpected_cmdline(node->content));
	return (NULL);
}
