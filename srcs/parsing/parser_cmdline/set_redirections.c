/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:41:46 by zwina             #+#    #+#             */
/*   Updated: 2022/06/06 12:38:10 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_redirections(t_list *reds)
{
	char	*token;
	size_t	len;

	while (reds)
	{
		if (reds->stat & RD)
		{
			token = get_rd_token(reds->content, &len);
			if (set_rds(reds, token, len))
			{
				errors(token, ERR_RD_INVALID, 0);
				free(token);
				return (1);
			}
			free(token);
		}
		reds = reds->next;
	}
	return (0);
}

int	set_rds(t_list *red, char *token, size_t len)
{
	if (!ft_strncmp(token, ">", len))
		set_rd(red, len, RD_OUTPUT);
	else if (!ft_strncmp(token, "<", len))
		set_rd(red, len, RD_INPUT);
	else if (!ft_strncmp(token, ">>", len))
		set_rd(red, len, RD_APPEND);
	else if (!ft_strncmp(token, "<<", len))
		set_rd(red, len, RD_HEREDOC);
	else
		return (1);
	return (0);
}

void	set_rd(t_list *red, int start, char rd_type)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	i = start;
	while (((char *)red->content)[i] == ' ')
		i++;
	len = ft_strlen(red->content + i);
	tmp = red->content;
	red->content = ft_substr(red->content, i, len);
	free(tmp);
	red->stat = red->stat | rd_type;
}

char	*get_rd_token(char *str, size_t *len)
{
	char	*token;
	size_t	i;

	i = 0;
	while (str[i] == '<' || str[i] == '>')
		i++;
	*len = i;
	token = ft_substr(str, 0, i);
	return (token);
}
