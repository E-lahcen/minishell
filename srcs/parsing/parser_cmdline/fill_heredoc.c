/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:43:22 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 14:14:25 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fill_heredoc(t_list *node)
{
	int		pipe_fd[2];
	char	*str;
	char	*limiter;
	size_t	size;

	if (g_global.heredoc_ctrlc == 1)
		return (-1337);
	pipe(pipe_fd);
	limiter = get_limiter(node->content);
	size = ft_strlen(limiter) + 1;
	str = readline("\e[38;5;208m> \e[0m");
	while (str && ft_strncmp(limiter, str, size))
	{
		filling(node, ft_strjoin(str, "\n"), pipe_fd[1]);
		free(str);
		str = readline("\e[38;5;208m> \e[0m");
	}
	free(str);
	free(limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	filling(t_list *node, char *str, int pipe_fd)
{
	if ((node->stat & QU) == 0)
		expand_dollars_heredoc(&str);
	write(pipe_fd, str, ft_strlen(str));
	free(str);
}

char	*get_limiter(char *limiter)
{
	size_t	i;
	size_t	len;
	char	*new_limiter;

	i = 0;
	len = 0;
	while (limiter[i])
	{
		if (limiter[i] != '\'' && limiter[i] != '\"' && \
	!(limiter[i] == '$' && (limiter[i + 1] == '\'' || limiter[i + 1] == '\"')))
			len++;
		i++;
	}
	new_limiter = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	len = 0;
	while (limiter[i])
	{
		if (limiter[i] != '\'' && limiter[i] != '\"' && \
	!(limiter[i] == '$' && (limiter[i + 1] == '\'' || limiter[i + 1] == '\"')))
			new_limiter[len++] = limiter[i];
		i++;
	}
	new_limiter[len] = '\0';
	return (new_limiter);
}

void	expand_dollars_heredoc(char **str)
{
	t_list	*hold;
	t_list	*node;
	t_list	*lsttmp;

	hold = parser_dollar_heredoc(*str);
	lsttmp = hold;
	while (lsttmp)
	{
		if (lsttmp->stat & DR)
			expand(lsttmp);
		lsttmp = lsttmp->next;
	}
	node = ft_lstnew(*str, 0);
	relink_double_quote(hold, node);
	*str = node->content;
	free(node);
}

t_list	*parser_dollar_heredoc(char *str)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i = i + 2;
		else if (str[i] == '$' && ft_isvalidvar(str[i + 1]))
			i = get_dollar(str, i, &lst);
		else
			i = get_in_elem(str, i, &lst);
	}
	return (lst);
}
