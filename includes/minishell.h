/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:36:50 by zwina             #+#    #+#             */
/*   Updated: 2022/07/19 14:47:29 by zwina            ###   ########.fr       */
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

// Signal types
# define HANDLER 1
# define IGNORE 2
# define DEFAULT 3

typedef struct s_global
{
	int		heredoc_newl;
	int		exit;
	int		heredoc_ctrlc;
	char	**env;
	t_list	*myenv;
}		t_global;

t_global	g_global;

t_list	*setup_my_env(char **env);
void	minishell_loop(void);

// ERRORS
void	errors(char *str, char *status, char quit);

// SIGNALS
void	ctrl_c_heredoc(int sig);
void	ctrl_c(int sig);
void	sig_handler(char type);

#endif