/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:10:53 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 17:53:47 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_export(t_cmdline *cmdline)
{
	size_t	i;
	t_list	*node;
	char	**args;
	char	**new_key_value;

	i = 0;
	args = ((t_cmd_infos *)cmdline->node->content)->cmd_args;
	if (args[1] == NULL && print_export())
		return ;
	while (args[++i])
	{
		if (!export_isvalid(args[i]))
			continue ;
		new_key_value = get_new_key_value(args[i]);
		node = search_key(new_key_value[0]);
		if (node && new_key_value[1])
		{
			free_paths(node->content);
			node->content = new_key_value;
		}
		else
			ft_lstadd_back(&g_global.myenv, ft_lstnew(new_key_value, 0));
	}
	g_global.exit = errno;
}

int	export_isvalid(char *arg)
{
	size_t	i;
	char	*var;
	char	*str;

	i = 0;
	if (arg[i] == '=')
		i = ft_strlen(arg);
	else
		while (arg[i] && arg[i] != '=')
			i++;
	var = ft_substr(arg, 0, i);
	if (!unset_isvalid(var))
	{
		str = ft_strjoin(var, ": not a valid identifier");
		errors("export", str, 0);
		free(str);
		errno = 1;
		free(var);
		return (0);
	}
	free(var);
	return (1);
}

char	**get_new_key_value(char *arg)
{
	size_t	equal;
	t_list	*node;
	char	**new_key_value;

	new_key_value = (char **)malloc(sizeof(char *) * 3);
	equal = 0;
	while (arg[equal] && arg[equal] != '=')
		equal++;
	new_key_value[0] = ft_substr(arg, 0, equal);
	if (arg[equal])
	{
		node = ft_lstnew(ft_strdup(arg + equal + 1), 0);
		node = parser_double_quote(node);
		new_key_value[1] = node->content;
		free(node);
	}
	else
		new_key_value[1] = NULL;
	new_key_value[2] = NULL;
	return (new_key_value);
}

t_list	*search_key(char *key)
{
	t_list	*env;
	char	**key_value;

	env = g_global.myenv;
	while (env)
	{
		key_value = env->content;
		if (!ft_strncmp(key_value[0], key, ft_strlen(key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	print_export(void)
{
	t_list	*env;
	char	**key_value;

	env = g_global.myenv;
	while (env)
	{
		key_value = env->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key_value[0], 1);
		if (key_value[1])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(key_value[1], 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (1);
}
