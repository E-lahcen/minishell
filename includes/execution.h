/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:22:48 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 11:40:49 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// Errors
# define CMD_NOT_FOUND "command not found"
# define CMD_NO_FILE_OR_DIR "No such file or directory"

// Pipestats
# define PAND (char)1
# define POR (char)2

// executor.c
void	executor(t_listline *listline);
// paths.c
char	**get_paths(char **env);
char	*env_searching(char *str, char **env);
void	free_paths(char **paths);

#endif