/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:08:37 by zwina             #+#    #+#             */
/*   Updated: 2022/07/22 12:32:29 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_cd(t_cmdline *cmdline)
{
	char *to_go;

	to_go = NULL;
	if (((t_cmd_infos *)cmdline->node->content)->cmd_args[1] == NULL)
		to_go = getmyenv("HOME");
	else
		to_go = ((t_cmd_infos *)cmdline->node->content)->cmd_args[1];
	if (to_go == NULL)
	{
		errors("cd", "HOME not set", 0);
		errno = 1;
	}
	else
		change_dir(to_go);
	g_global.exit = errno;
}

void change_dir(char *to_go)
{
	int rt;
	char *tmp;
	char *str;

	rt = chdir(to_go);
	if (rt == -1 && to_go[0])
	{
		tmp = ft_strjoin(": ", strerror(errno));
		str = ft_strjoin(to_go, tmp);
		errors("cd", str, 0);
		free(tmp);
		free(str);
		errno = 1;
	}
	else if (to_go[0])
		set_pwd_variable();
}

void set_pwd_variable(void)
{
	char **key_value;
	t_list *env;

	env = g_global.myenv;
	while (env)
	{
		key_value = env->content;
		if (!ft_strncmp(key_value[0], "PWD", 4))
		{
			set_oldpwd_variable(key_value[1]);
			free(key_value[1]);
			key_value[1] = NULL;
			key_value[1] = getcwd(key_value[1], 0);
			break;
		}
		env = env->next;
	}
}

void set_oldpwd_variable(char *oldpwd)
{
	char **key_value;
	t_list *env;

	env = g_global.myenv;
	while (env)
	{
		key_value = env->content;
		if (!ft_strncmp(key_value[0], "OLDPWD", 7))
		{
			free(key_value[1]);
			key_value[1] = ft_strdup(oldpwd);
			break;
		}
		env = env->next;
	}
}
