/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:57:59 by zwina             #+#    #+#             */
/*   Updated: 2022/07/21 09:49:00 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
	{
		errors(NULL, "Arguments are not supported.", 0);
		return (1);
	}
	g_global.heredoc_newl = 0;
	g_global.exit = 0;
	g_global.heredoc_ctrlc = 0;
	g_global.env = env;
	g_global.myenv = setup_my_env(env);
	sig_handler(HANDLER);
	minishell_loop();
	return (0);
}

t_list	*setup_my_env(char **env)
{
	size_t	i;
	size_t	equal_index;
	t_list	*my_env;
	char	**key_value;

	i = 0;
	my_env = NULL;
	while (env[i])
	{
		equal_index = 0;
		while (env[i][equal_index] && env[i][equal_index] != '=')
			equal_index++;
		key_value = (char **)malloc(sizeof(char *) * 3);
		key_value[0] = ft_substr(env[i], 0, equal_index);
		key_value[1] = ft_strdup(env[i] + equal_index + 1);
		key_value[2] = NULL;
		ft_lstadd_back(&my_env, ft_lstnew(key_value, 0));
		i++;
	}
	return (my_env);
}

void	minishell_loop(void)
{
	t_listline	*shelline;
	char		*line;

	while (1)
	{
		line = readline("\e[38;5;118mminishell$\e[0m ");
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		g_global.heredoc_ctrlc = 0;
		g_global.heredoc_newl = 0;
		shelline = parser_shelline(line);
		if (!shelline)
			continue ;
		executor_shelline(shelline);
		free_listline(shelline);
	}
}
