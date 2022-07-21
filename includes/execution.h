/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:22:48 by zwina             #+#    #+#             */
/*   Updated: 2022/07/20 13:19:41 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

// Errors
#define ERR_CMDNOTFOUND "command not found"
#define ERR_NOSUCHFILE "no such file or directory"
#define ERR_ISDIR "Is a directory"
#define ERR_PERMISSION "Permission denied"
#define ERR_AMBG "ambiguous redirect"

// Pipestats
#define PAND (char)16
#define POR (char)32

// executor_shelline.c
int check_symbol(t_list *node);
void executor_shelline(t_listline *shelline);
// executor_listline.c
void executor_listline(t_cmdline *cmdline);
// executor_pipeline.c
pid_t executor_pipeline(t_pipeline *pipeline);
pid_t executor_pipeline_loop(t_list *cmdlines, int *pipe_fd);
void dup_close_pipe(int *pipe_fd, int standard);
// executor_cmdline.c
void executor_cmdline(t_cmdline *cmdline, char built);
void execute(t_cmdline *cmdline);
int is_builtins(char *cmd);
void execute_builtins(t_cmdline *cmdline);
void execve_errors(char *cmd_path);
char **convert_my_env(t_list *my_env);

// paths.c
char **get_paths(void);
char *getmyenv(char *name);
void free_paths(void *ptr);

// set_files.c
int set_files(t_cmdline *cmdline);
t_list *parser_file(t_list *red);
int open_file(t_cmdline *cmdline, t_list *red);
int open_out_file(t_cmdline *cmdline, t_list *red);
int open_in_file(t_cmdline *cmdline, t_list *red);

// BUILTINS

//	echo.c
void ft_echo(t_cmdline *cmdline);
size_t skip_minus_n(char **args);
int is_minus_n(char *arg);
//	cd.c
void ft_cd(t_cmdline *cmdline);
void change_dir(char *to_go);
void set_pwd_variable(void);
void set_oldpwd_variable(char *oldpwd);
//	pwd.c
void ft_pwd(t_cmdline *cmdline);
//	export.c
void ft_export(t_cmdline *cmdline);
int export_isvalid(char *arg);
char **get_new_key_value(char *arg);
t_list *search_key(char *key);
int print_export(void);
//	unset.c
void ft_unset(t_cmdline *cmdline);
int unset_isvalid(char *var);
void unsetting(char *name);
void unsetting_loop(char *name);
//	env.c
void ft_env(t_cmdline *cmdline);
void print_env(char **key_value);
//	exit.c
void ft_exit(t_cmdline *cmdline);
void exiting(int status);
int ft_isnumeric(char *str);
int get_sign(char **first_arg);

#endif