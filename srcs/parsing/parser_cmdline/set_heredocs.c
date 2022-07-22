/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:30:55 by zwina             #+#    #+#             */
/*   Updated: 2022/07/22 14:24:12 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void set_heredocs_listline(t_listline *listline)
{
	t_list *lsttmp;

	lsttmp = listline->pipelines;
	while (lsttmp)
	{
		if (lsttmp->stat == PIPELINE)
			set_heredocs_pipeline(lsttmp->content);
		lsttmp = lsttmp->next;
	}
}

void set_heredocs_pipeline(t_pipeline *pipeline)
{
	t_list *lsttmp;

	lsttmp = pipeline->cmdlines;
	while (lsttmp)
	{
		if (lsttmp->stat == CMDLINE)
			set_heredocs_cmdline(lsttmp->content);
		lsttmp = lsttmp->next;
	}
}

void set_heredocs_cmdline(t_cmdline *cmdline)
{
	t_list *wrds;

	if (cmdline->node->stat == LISTLINE)
		set_heredocs_listline(cmdline->node->content);
	wrds = cmdline->words[1];
	while (wrds)
	{
		if ((wrds->stat & RD_HEREDOC) && cmdline->n_heredoc)
		{
			cmdline->o_a_i_h[3] = fill_heredoc(wrds);
			cmdline->n_heredoc--;
		}
		wrds = wrds->next;
	}
}

void set_limiter(char *limiter, char *new_limiter)
{
	size_t i;
	size_t len;
	char q;

	i = 0;
	len = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
		{
			q = limiter[i++];
			while (limiter[i] != q)
				new_limiter[len++] = limiter[i++];
		}
		else if (!(limiter[i] == '$' && (limiter[i + 1] == '\'' || limiter[i + 1] == '\"')))
			new_limiter[len++] = limiter[i];
		i++;
	}
	new_limiter[len] = '\0';
}
