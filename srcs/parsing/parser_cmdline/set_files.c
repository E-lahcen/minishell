/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:54:14 by zwina             #+#    #+#             */
/*   Updated: 2022/06/06 09:28:01 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_files(t_cmdline **cmdline, t_list *reds)
{
	t_list	*lsttmp;
	t_list	*red;

	lsttmp = reds;
	while (lsttmp)
	{
		if ((lsttmp->stat & RD) && (lsttmp->stat & RD_HEREDOC) == 0)
		{
			red = parser_file(lsttmp, (*cmdline)->env);
			if (red == NULL || ft_lstsize(red) > 1)
			{
				errors(lsttmp->content, ERR_RD_AMBG, 0);
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

t_list	*parser_file(t_list *red, char **env)
{
	t_list	*elems;

	elems = parser_arg(red, env);
	if (elems)
		elems->stat = red->stat;
	return (elems);
}

int	open_file(t_cmdline **cmdline, t_list *red)
{
	if (open_out_file(cmdline, red))
		return (1);
	else if (open_in_file(cmdline, red))
		return (1);
	return (0);
}

int	open_out_file(t_cmdline **cmdline, t_list *red)
{
	if (red->stat & RD_OUTPUT)
	{
		(*cmdline)->output = open(red->content, \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if ((*cmdline)->output == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
	}
	else if (red->stat & RD_APPEND)
	{
		(*cmdline)->append = open(red->content, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		if ((*cmdline)->append == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
	}
	return (0);
}

int	open_in_file(t_cmdline **cmdline, t_list *red)
{
	if (red->stat & RD_INPUT)
	{
		(*cmdline)->input = open(red->content, O_RDONLY);
		if ((*cmdline)->input == -1)
		{
			errors(red->content, strerror(errno), 0);
			return (1);
		}
	}
	printf("in\n");
	return (0);
}
