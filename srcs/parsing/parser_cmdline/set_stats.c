/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:55:11 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 12:04:15 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_stats(t_list *reds)
{
	uint16_t	last_stat;

	while (reds)
	{
		if (!ft_strncmp(reds->content, "<<", 3))
			last_stat = set_stat_symbol(reds, S_HEREDOC);
		else if (!ft_strncmp(reds->content, "<", 2))
			last_stat = set_stat_symbol(reds, S_INPUT);
		else if (!ft_strncmp(reds->content, ">>", 3))
			last_stat = set_stat_symbol(reds, S_APPEND);
		else if (!ft_strncmp(reds->content, ">", 2))
			last_stat = set_stat_symbol(reds, S_OUTPUT);
		else
			last_stat = set_stat_arg(reds, last_stat);
		reds = reds->next;
	}
}

uint16_t	set_stat_symbol(t_list *red, uint16_t stat)
{
	red->stat = red->stat | stat;
	return (stat);
}

uint16_t	set_stat_arg(t_list *red, uint16_t last_stat)
{
	uint16_t	stat;

	stat = 0;
	if (last_stat == S_HEREDOC)
		stat = RD_HEREDOC;
	else if (last_stat == S_INPUT)
		stat = RD_INPUT;
	else if (last_stat == S_APPEND)
		stat = RD_APPEND;
	else if (last_stat == S_OUTPUT)
		stat = RD_OUTPUT;
	red->stat = red->stat | stat;
	return (stat);
}
