/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:36:50 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 15:17:09 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

# include "libft.h"
# include "parsing.h"
# include "execution.h"

extern int	g_exit;

// PRINTING
void	print_listline(t_listline *listline);
void	print_pipeline(t_pipeline *pipeline);
void	print_cmdline(t_cmdline *cmdline);
void	print_list(t_list *words);

// ERRORS
void	errors(char *str, char *status, char quit);

#endif