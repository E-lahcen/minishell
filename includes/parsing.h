/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:37:49 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 07:46:38 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Errors
# define ERR_QUOTES "unclosed quotes are not supported"
# define ERR_AMBG "ambiguous redirect"
# define ERR_UNEX "syntax error near unexpected token"
# define ERR_INCP "incomplete symbol"
# define ERR_PARTH_C "unclosed parenthesis"
# define ERR_PARTH_E "empty parenthesis"
# define ERR_PARTH_S "syntax error parenthesis"

// Stats
# define QU (unsigned short)96
# define SQU (unsigned short)64
# define DQU (unsigned short)32
# define DR (unsigned short)16
# define RD (unsigned short)15
# define RD_HEREDOC (unsigned short)8
# define RD_INPUT (unsigned short)4
# define RD_APPEND (unsigned short)2
# define RD_OUTPUT (unsigned short)1

// Symbols
# define SYMBOL (unsigned short)32512
# define S_OAP (unsigned short)28672
# define S_OR (unsigned short)16384
# define S_AND (unsigned short)8192
# define S_PIPE (unsigned short)4096
# define S_RD (unsigned short)3840
# define S_HEREDOC (unsigned short)2048
# define S_INPUT (unsigned short)1024
# define S_APPEND (unsigned short)512
# define S_OUTPUT (unsigned short)256

// Stract nodes
# define LISTLINE (unsigned short)4
# define PIPELINE (unsigned short)2
# define CMDLINE (unsigned short)1

// Dollar nodes
# define F_NODE (char)2
# define L_NODE (char)1

// Dollar types
# define INTEROGATION (char)1
# define ALPHA (char)2
# define DOLLAR (char)3

typedef struct s_listline
{
	t_list	*pipelines;
	int		n;
}			t_listline;

typedef struct s_pipeline
{
	t_list	*cmdlines;
	int		n;
}			t_pipeline;

typedef struct s_cmdline
{
	t_list	**words;
	char	*cmd_path;
	char	**cmd_args;
	char	redirections;
	int		output;
	int		append;
	int		input;
	int		heredoc;
	char	**env;
}			t_cmdline;

// ----------------------------------------------------------------------------
// parser.c
t_listline	*parser(char *line, char **env);
size_t		skip_parenthesis(char *line, size_t i);
size_t		skip_quotes(char *line, size_t i);
// error_parsing.c
int			error_quotes(char *line);
int			error_parenthesis(char *line);
int			error_incomplete(char *line);
int			error_unexpected_listline(t_listline *listline);
int			error_unexpected_pipeline(t_pipeline *pipeline);
int			error_unexpected_cmdline(t_cmdline *cmdline);
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// parser_listline.c
t_listline	*parser_listline(char *line, char **env);
size_t		listline_loop(char *line, size_t i, t_list **pipeline, char **env);
size_t		get_symbols(char *line, size_t start, t_list **listline);
size_t		get_parenthesis_listline(char *line, size_t start, t_list **list, \
char **env);
size_t		get_listline(char *line, size_t start, t_list **listline, \
char **env);
// error_parenthesis.c
int			closed_parenthesis(char *line);
int			empty_parenthesis(char *line);
int			symbols_parenthesis(char *line);
int			open_parenthesis(char *line, size_t i);
int			close_parenthesis(char *line, size_t i);
// free_listline.c
void		free_listline(t_listline *listline);
void		free_pipeline(t_pipeline *pipeline);
void		free_cmdline(t_cmdline *cmdline);
// ----------------------------------------------------------------------------
// parser_pipeline.c
t_pipeline	*parser_pipeline(char *line, char **env);
size_t		pipeline_loop(char *line, size_t i, t_list **pipeline, char **env);
size_t		get_pipe(char *line, size_t start, t_list **listline);
size_t		get_parenthesis_pipeline(char *line, size_t start, t_list **list, \
char **env);
size_t		get_pipeline(char *line, size_t start, t_list **listline, \
char **env);
// ----------------------------------------------------------------------------
// parser_cmdline.c
t_cmdline	*parser_cmdline(char *line, char **env);
void		free_all(t_cmdline *cmdline, t_list **words, char *line);
// parser_word.c
t_list		**parser_word(char *line);
size_t		get_redirection(char *line, size_t start, t_list **reds);
size_t		get_arg(char *line, size_t start, t_list **args);
size_t		set_q_d(char *line, size_t i, char *q_d);
// ----------------------------------------------------------------------------
// expand_args.c
t_list		*expand_args(t_list *args, char **env);
void		expand_args_loop(t_list *args, char **env);
t_list		*parser_arg(t_list *arg, char **env);
size_t		get_elems(char *content, size_t i, t_list **elems);
void		reset_stat(t_list *elems);
// expand_astrisk.c
void		expand_astrisk(t_list *args);
void		expand_astrisk_loop(t_list *args);
t_list		*parser_astrisk(void);
int			is_astrisk(t_list *node);
// expand_dollars.c
t_list		*expand_dollars(t_list *elems, char **env);
void		expand_dollars_loop(t_list *elems, char **env);
t_list		*parser_dollar(t_list *node, char **env);
size_t		get_node(char *str, size_t start, t_list **minielems, char pos);
// expand_quotes.c
t_list		*expand_quotes(t_list *elems, char **env);
t_list		*parser_double_quote(t_list *node, char **env);
size_t		get_minielems(char *content, size_t i, t_list **minielems);
// get_elements.c
size_t		get_quote(char *str, size_t start, t_list **elem, uint16_t stat);
size_t		get_dollar(char *str, size_t start, t_list **elem);
size_t		get_in_elem(char *str, size_t start, t_list **elem);
size_t		get_out_elem(char *str, size_t start, t_list **elem);
size_t		get_symbol(char *line, size_t start, t_list **words);
// set_stats.c
void		set_stats(t_list *reds);
uint16_t	set_stat_symbol(t_list *red, uint16_t stat);
uint16_t	set_stat_arg(t_list *red, uint16_t stat);
// set_redirections.c
int			set_redirections(t_list *reds);
int			set_rds(t_list *red, char *token, size_t len);
void		set_rd(t_list *red, int start, char rd_type);
char		*get_rd_token(char *str, size_t *len);
// set_heredoc.c
int			set_heredoc(t_cmdline *cmdline);
char		*get_limiter(char *limiter);
int			fill_heredoc(char *limiter, char **env, char stat);
void		expand_dollars_heredoc(char **str, char **env);
t_list		*parser_dollar_heredoc(char *str);
// set_files.c
int			set_files(t_cmdline **cmdline, t_list *reds);
t_list		*parser_file(t_list *red, char **env);
int			open_file(t_cmdline **cmdline, t_list *red);
int			open_out_file(t_cmdline **cmdline, t_list *red);
int			open_in_file(t_cmdline **cmdline, t_list *red);
// expanding_relinking.c
void		expand(t_list *node, char **env);
void		relink_double_quote(t_list *minielems, t_list *node);
t_list		*relink_arg(t_list	*elems);
// fill_cmdline.c
void		init_cmdline(t_cmdline *cmdline, char **env);
void		fill_cmdline(t_cmdline *cmdline);
void		fill_cmd_args(t_cmdline *cmdline, t_list *args);
void		fill_cmd_path(t_cmdline *cmdline);
// ----------------------------------------------------------------------------
#endif