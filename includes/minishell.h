/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:36:50 by zwina             #+#    #+#             */
/*   Updated: 2022/06/15 13:29:11 by lelhlami         ###   ########.fr       */
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
void	print_listline(t_listline *listline, size_t tabs);
void	print_pipeline(t_pipeline *pipeline, size_t tabs);
void	print_cmdline(t_cmdline *cmdline, size_t tabs);
void	print_list(t_list *words, size_t tabs);
void	print_tabs(size_t tabs);

// ERRORS
void	errors(char *str, char *status, char quit);

// SIGNALS
void	sighandler(void);
void	ctrl_d_func(void);

#endif