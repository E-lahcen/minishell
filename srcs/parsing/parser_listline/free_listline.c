/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_listline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:22:54 by zwina             #+#    #+#             */
/*   Updated: 2022/06/12 13:22:39 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_listline(t_listline *listline)
{
	t_list	*lst;
	t_list	*tmp;

	if (!listline)
		return ;
	lst = listline->pipelines;
	while (lst)
	{
		if (lst->stat == S_AND || lst->stat == S_OR)
			free(lst->content);
		else if (lst->stat == LISTLINE)
			free_listline(lst->content);
		else if (lst->stat == PIPELINE)
			free_pipeline(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	free(listline);
}

void	free_pipeline(t_pipeline *pipeline)
{
	t_list	*lst;
	t_list	*tmp;

	if (!pipeline)
		return ;
	lst = pipeline->cmdlines;
	while (lst)
	{
		if (lst->stat == S_PIPE)
			free(lst->content);
		else if (lst->stat == LISTLINE)
			free_listline(lst->content);
		else if (lst->stat == CMDLINE)
			free_cmdline(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	free(pipeline);
}

void	free_cmdline(t_cmdline *cmdline)
{
	if (!cmdline)
		return ;
	ft_lstclear(&cmdline->words[0], free);
	ft_lstclear(&cmdline->words[1], free);
	free(cmdline->words);
	free_paths(cmdline->cmd_args);
	free(cmdline->cmd_path);
	close(cmdline->output);
	close(cmdline->append);
	close(cmdline->input);
	close(cmdline->heredoc);
	free(cmdline);
}
