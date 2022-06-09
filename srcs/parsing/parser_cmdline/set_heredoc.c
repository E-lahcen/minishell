/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:43:22 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 09:00:39 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_heredoc(t_cmdline *cmdline)
{
	t_list	*reds;
	size_t	n;
	int		error;

	reds = cmdline->words[1];
	n = 0;
	error = 0;
	while (reds && reds->next)
	{
		if ((reds->stat & SYMBOL) && (reds->next->stat & SYMBOL))
		{
			errors(reds->next->content, ERR_UNEX, 0);
			return (1);
		}
		else if ((reds->next->stat & RD_HEREDOC))
		{
			if (cmdline->heredoc != -1337)
				close(cmdline->heredoc);
			cmdline->heredoc = fill_heredoc(\
			get_limiter(reds->next->content), cmdline->env, reds->next->stat);
		}
		reds = reds->next;
	}
	return (error);
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

int	fill_heredoc(char *limiter, char **env, char stat)
{
	int		pipe_fd[2];
	size_t	size;
	char	*str;

	pipe(pipe_fd);
	close(pipe_fd[1]);
	size = ft_strlen(limiter) + 1;
	str = readline("\e[38;5;208m> \e[0m");
	while (str && ft_strncmp(limiter, str, size))
	{
		if ((stat & QU) == 0)
			expand_dollars_heredoc(&str, env);
		write(pipe_fd[1], str, ft_strlen(str));
		free(str);
		str = readline("\e[38;5;208m> \e[0m");
	}
	free(str);
	free(limiter);
	return (pipe_fd[0]);
}

void	expand_dollars_heredoc(char **str, char **env)
{
	t_list	*hold;
	t_list	*node;
	t_list	*lsttmp;

	hold = parser_dollar_heredoc(*str);
	lsttmp = hold;
	while (lsttmp)
	{
		if (lsttmp->stat & DR)
			expand(lsttmp, env);
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
