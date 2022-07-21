/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:10:06 by zwina             #+#    #+#             */
/*   Updated: 2022/06/23 12:10:59 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_cmdline *cmdline)
{
	char	*str;

	(void)cmdline;
	str = NULL;
	str = getcwd(str, 0);
	ft_putendl_fd(str, 1);
	free(str);
	g_global.exit = errno;
}
