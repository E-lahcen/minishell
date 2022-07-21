/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:09:59 by lelhlami          #+#    #+#             */
/*   Updated: 2022/07/20 20:58:20 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_paths(void)
{
	char	**paths;
	char	*tmp;
	size_t	i;

	tmp = getmyenv("PATH");
	paths = ft_split(tmp, ':');
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	*getmyenv(char *name)
{
	t_list	*env;
	char	**key_value;

	env = g_global.myenv;
	while (env)
	{
		key_value = env->content;
		if (!ft_strncmp(name, key_value[0], ft_strlen(name) + 1))
			return (key_value[1]);
		env = env->next;
	}
	return (NULL);
}

void	free_paths(void *ptr)
{
	char	**paths;
	size_t	i;

	paths = (char **)ptr;
	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i++]);
	}
	free(paths);
}

char	**convert_myenv(void)
{
	int		i;
	int		size;
	char	*tmp;
	char	**newenv;
	t_list	*env;

	env = g_global.myenv;
	size = ft_lstsize(env) + 1;
	newenv = (char **)malloc(sizeof(char *) * size);
	i = 0;
	while (env)
	{
		if (((char **)env->content)[1])
		{
			tmp = ft_strjoin(((char **)env->content)[0], "=");
			newenv[i] = ft_strjoin(tmp, ((char **)env->content)[1]);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	newenv[i] = NULL;
	return (newenv);
}
