/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:30:55 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 13:19:57 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_heredocs_listline(t_listline *listline)
{
	t_list	*lsttmp;

	lsttmp = listline->pipelines;
	while (lsttmp)
	{
		if (lsttmp->stat == PIPELINE)
			set_heredocs_pipeline(lsttmp->content);
		lsttmp = lsttmp->next;
	}
}

void	set_heredocs_pipeline(t_pipeline *pipeline)
{
	t_list	*lsttmp;

	lsttmp = pipeline->cmdlines;
	while (lsttmp)
	{
		if (lsttmp->stat == CMDLINE)
			set_heredocs_cmdline(lsttmp->content);
		lsttmp = lsttmp->next;
	}
}

void	set_heredocs_cmdline(t_cmdline *cmdline)
{
	t_list	*wrds;

	if (cmdline->node->stat == LISTLINE)
		set_heredocs_listline(cmdline->node->content);
	wrds = cmdline->words[1];
	while (wrds)
	{
		if (wrds->stat == RD_HEREDOC && cmdline->n_heredoc)
		{
			cmdline->o_a_i_h[3] = fill_heredoc(wrds);
			cmdline->n_heredoc--;
		}
		wrds = wrds->next;
	}
}
