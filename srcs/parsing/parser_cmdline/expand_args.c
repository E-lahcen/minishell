/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:29:29 by zwina             #+#    #+#             */
/*   Updated: 2022/06/08 13:27:31 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// echo $USER$HOME -> you have to fix it

t_list	*expand_args(t_list *args, char **env)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (args)
	{
		if (((args->stat & QU) || (args->stat & DR)) && \
			!(args->stat & RD_HEREDOC))
		{
			lsttmp = args->next;
			lsttmp2 = args;
			args = parser_arg(args, env);
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
	expand_args_loop(args, env);
	return (args);
}

void	expand_args_loop(t_list *args, char **env)
{
	t_list	*lsttmp;
	t_list	*lsttmp2;

	while (args && args->next)
	{
		if (((args->next->stat & QU) || (args->next->stat & DR)) && \
			!(args->next->stat & RD_HEREDOC))
		{
			lsttmp = args->next->next;
			lsttmp2 = args->next;
			args->next = parser_arg(args->next, env);
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

t_list	*parser_arg(t_list *arg, char **env)
{
	t_list	*elems;
	size_t	i;

	elems = NULL;
	i = 0;
	while (((char *)arg->content)[i] != '\0' && \
	((char *)arg->content)[i] != '&' && ((char *)arg->content)[i] != '|')
		i = get_elems(arg->content, i, &elems);
	elems = expand_dollars(elems, env);
	elems = expand_quotes(elems, env);
	reset_stat(relink_arg(elems));
	return (elems);
}

size_t	get_elems(char *content, size_t i, t_list **elems)
{
	if (content[i] == '$' && \
		(ft_isdigit_z(content[i + 1]) || content[i + 1] == '*'))
		i = i + 2;
	else if (content[i] == '$' && \
	(content[i + 1] == '\'' || content[i + 1] == '\"'))
		i = i + 1;
	else if (content[i] == '$' && ft_isvalidvar(content[i + 1]))
		i = get_dollar(content, i, elems);
	else if (content[i] == '\'')
		i = get_quote(content, i, elems, SQU);
	else if (content[i] == '\"')
		i = get_quote(content, i, elems, DQU);
	else
		i = get_out_elem(content, i, elems);
	return (i);
}

void	reset_stat(t_list *elems)
{
	while (elems)
	{
		elems->stat = 0;
		elems = elems->next;
	}
}
