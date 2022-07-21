/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:11:39 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 17:29:13 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_unset(t_cmdline *cmdline)
{
	size_t	i;
	char	**args;
	char	*str;

	i = 0;
	args = ((t_cmd_infos *)cmdline->node->content)->cmd_args;
	while (args[++i])
	{
		if (!unset_isvalid(args[i]))
		{
			str = ft_strjoin(args[i], ": not a valid identifier");
			errors("unset", str, 0);
			free(str);
			errno = 1;
		}
		else
			unsetting(args[i]);
	}
	g_global.exit = errno;
}

int	unset_isvalid(char *var)
{
	size_t	i;

	i = 0;
	if (var[i] == '\0')
		return (0);
	while (var[i])
	{
		if (i == 0 && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		else if (!ft_isdigit(var[i]) && !ft_isalpha(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unsetting(char *name)
{
	char	**key_value;
	t_list	*lsttmp;

	if (!g_global.myenv)
		return ;
	key_value = g_global.myenv->content;
	if (!ft_strncmp(name, key_value[0], ft_strlen(name) + 1))
	{
		lsttmp = g_global.myenv;
		g_global.myenv = g_global.myenv->next;
		ft_lstdelone(lsttmp, free_paths);
	}
	else
		unsetting_loop(name);
}

void	unsetting_loop(char *name)
{
	char	**key_value;
	t_list	*lsttmp;
	t_list	*lsttmp2;

	lsttmp = g_global.myenv;
	while (lsttmp->next)
	{
		key_value = lsttmp->next->content;
		if (!ft_strncmp(name, key_value[0], ft_strlen(name) + 1))
		{
			lsttmp2 = lsttmp->next;
			lsttmp->next = lsttmp2->next;
			ft_lstdelone(lsttmp2, free_paths);
			break ;
		}
		lsttmp = lsttmp->next;
	}
}
