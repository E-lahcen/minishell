/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:09:59 by lelhlami          #+#    #+#             */
/*   Updated: 2022/06/06 12:03:24 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_paths(char **env)
{
	char	**paths;
	char	*tmp;
	size_t	i;

	tmp = env_searching(ft_strdup("PATH="), env);
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

char	*env_searching(char *str, char **env)
{
	int		i;
	size_t	bytes;

	i = 0;
	bytes = ft_strlen(str);
	while (env[i] && ft_strncmp(str, env[i], bytes))
		i++;
	free(str);
	if (!env[i])
		return (NULL);
	return (ft_strchr(env[i], '=') + 1);
}

void	free_paths(char **paths)
{
	size_t	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
