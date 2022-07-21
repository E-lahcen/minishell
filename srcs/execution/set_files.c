/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:54:14 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 12:45:55 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_files(t_cmdline *cmdline)
{
	t_list	*lsttmp;
	t_list	*red;

	lsttmp = cmdline->words[1];
	while (lsttmp)
	{
		if (lsttmp->stat & RD)
		{
			red = parser_file(lsttmp);
			if (red == NULL)
			{
				ft_lstclear(&red, free);
				return (1);
			}
			else if (open_file(cmdline, red))
			{
				ft_lstclear(&red, free);
				return (1);
			}
			ft_lstclear(&red, free);
		}
		lsttmp = lsttmp->next;
	}
	return (0);
}

t_list	*parser_file(t_list *red)
{
	t_list	*elems;

	if ((red->stat & ASTRISK) && red->next && (red->next->stat & ASTRISK))
	{
		errors("*", ERR_AMBG, 1);
		return (NULL);
	}
	elems = parser_arg(red);
	if (elems)
		elems->stat = red->stat;
	if (!elems || ft_lstsize(elems) > 1)
	{
		errors(red->content, ERR_AMBG, 1);
		return (NULL);
	}
	return (elems);
}

int	open_file(t_cmdline *cmdline, t_list *red)
{
	if (open_out_file(cmdline, red))
		return (1);
	else if (open_in_file(cmdline, red))
		return (1);
	return (0);
}

int	open_out_file(t_cmdline *cmdline, t_list *red)
{
	if (red->stat & RD_OUTPUT)
	{
		close(cmdline->o_a_i_h[1]);
		cmdline->o_a_i_h[0] = open(red->content, \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (cmdline->o_a_i_h[0] == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
		cmdline->redirections = (cmdline->redirections & 13) | 1;
	}
	else if (red->stat & RD_APPEND)
	{
		close(cmdline->o_a_i_h[0]);
		cmdline->o_a_i_h[1] = open(red->content, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmdline->o_a_i_h[1] == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
		cmdline->redirections = (cmdline->redirections & 14) | 2;
	}
	return (0);
}

int	open_in_file(t_cmdline *cmdline, t_list *red)
{
	if (red->stat & RD_INPUT)
	{
		cmdline->o_a_i_h[2] = open(red->content, O_RDONLY);
		if (cmdline->o_a_i_h[2] == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
		cmdline->redirections = (cmdline->redirections & 7) | 4;
	}
	if (red->stat & RD_HEREDOC)
	{
		close(cmdline->o_a_i_h[2]);
		cmdline->redirections = (cmdline->redirections & 11) | 8;
	}
	return (0);
}
