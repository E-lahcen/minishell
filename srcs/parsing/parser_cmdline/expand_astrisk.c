/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_astrisk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:10:44 by zwina             #+#    #+#             */
/*   Updated: 2022/07/22 16:35:46 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*expand_astrisk(t_list *args)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (args)
	{
		if (is_astrisk(args))
		{
			lsttmp = args->next;
			lsttmp2 = args;
			args = parser_astrisk();
			ft_lstdelone(lsttmp2, free);
			if (args)
			{
				(ft_lstlast(args))->next = lsttmp;
				break ;
			}
			args = lsttmp;
		}
		else
			break ;
	}
	expand_astrisk_loop(args);
	return (args);
}

void	expand_astrisk_loop(t_list *args)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (args && args->next)
	{
		if (is_astrisk(args->next))
		{
			lsttmp = args->next->next;
			lsttmp2 = args->next;
			args->next = parser_astrisk();
			ft_lstdelone(lsttmp2, free);
			if (args->next)
				(ft_lstlast(args->next))->next = lsttmp;
			else
				args->next = lsttmp;
		}
		else
			args = args->next;
	}
}

t_list	*parser_astrisk(void)
{
	t_list			*files;
	struct dirent	*pdent;
	DIR				*pd;
	char			*str;

	files = NULL;
	str = NULL;
	str = getcwd(str, 0);
	pd = opendir(str);
	free(str);
	pdent = readdir(pd);
	while (pdent)
	{
		if (pdent->d_name[0] != '.')
			ft_lstadd_back(&files, ft_lstnew(ft_strdup(pdent->d_name), \
				ASTRISK));
		pdent = readdir(pd);
	}
	closedir(pd);
	return (files);
}

int	is_astrisk(t_list *node)
{
	char	*str;
	size_t	i;

	if (node->stat & RD_HEREDOC)
		return (0);
	str = node->content;
	i = 0;
	while (str[i] == '*')
		i++;
	if (str[i])
		return (0);
	return (1);
}
