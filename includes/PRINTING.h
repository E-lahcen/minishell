#ifndef PRINTING_H
# define PRINTING_H

void	print_listline(t_listline *listline, size_t tabs);
void	print_pipeline(t_pipeline *pipeline, size_t tabs);
void	print_cmdline(t_cmdline *cmdline, size_t tabs);
void	print_args(t_cmd_infos *cmd_infos, size_t tabs);
void	print_reds(int *o_a_i_h, t_list *reds, size_t tabs);
void	print_list(t_list *words, size_t tabs);
void	print_tabs(size_t tabs);
void	print_my_env(t_list *env);

#endif