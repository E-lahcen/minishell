/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unexpected.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:34:06 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 08:16:11 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	error_unexpected_listline(t_listline *listline)
{
	t_list	*lsttmp;
	size_t	pattern;

	lsttmp = listline->pipelines;
	pattern = 1;
	while (lsttmp)
	{
		if ((lsttmp->stat == S_AND || lsttmp->stat == S_OR) && \
			pattern % 2 == 1)
			return (1);
		else if (lsttmp->stat == LISTLINE && \
			error_unexpected_listline(lsttmp->content))
			return (1);
		else if (lsttmp->stat == PIPELINE && \
			error_unexpected_pipeline(lsttmp->content))
			return (1);
		lsttmp = lsttmp->next;
		pattern++;
	}
	return (0);
}

int	error_unexpected_pipeline(t_pipeline *pipeline)
{
	t_list	*lsttmp;
	size_t	pattern;

	lsttmp = pipeline->cmdlines;
	pattern = 1;
	while (lsttmp)
	{
		if (lsttmp->stat == S_PIPE && pattern % 2 == 1)
			return (1);
		else if (lsttmp->stat == LISTLINE && \
			error_unexpected_listline(lsttmp->content))
			return (1);
		else if (lsttmp->stat == CMDLINE && \
			error_unexpected_cmdline(lsttmp->content))
			return (1);
		lsttmp = lsttmp->next;
		pattern++;
	}
	return (0);
}

int	error_unexpected_cmdline(t_cmdline *cmdline)
{
	t_list	*lsttmp;
	size_t	pattern;

	lsttmp = cmdline->words[1];
	pattern = 1;
	while (lsttmp)
	{
		if ((lsttmp->stat & S_RD) && pattern % 2 == 0)
			return (1);
		lsttmp = lsttmp->next;
		pattern++;
	}
	return (0);
}
