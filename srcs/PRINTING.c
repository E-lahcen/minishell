/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRINTING.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:06:17 by zwina             #+#    #+#             */
/*   Updated: 2022/07/18 16:31:08 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_listline(t_listline *listline, size_t tabs)
{
	t_list *lst;

	if (!listline)
	{
		print_tabs(tabs);
		printf("shelline : (NULL)\n");
		return;
	}
	print_tabs(tabs);
	if (tabs)
		printf("listline : n = %d.\n", listline->n);
	else
		printf("shelline : n = %d.\n", listline->n);
	lst = listline->pipelines;
	while (lst)
	{
		if (lst->stat == PIPELINE)
			print_pipeline(lst->content, tabs + 1);
		else if (lst->stat == S_OR)
		{
			print_tabs(tabs + 1);
			printf("[%s] : (S_OR).\n", lst->content);
		}
		else if (lst->stat == S_AND)
		{
			print_tabs(tabs + 1);
			printf("[%s] : (S_AND).\n", lst->content);
		}
		lst = lst->next;
	}
}

void print_pipeline(t_pipeline *pipeline, size_t tabs)
{
	t_list *lst;

	if (!pipeline)
	{
		print_tabs(tabs);
		printf("pipeline : (NULL)\n");
		return;
	}
	print_tabs(tabs);
	printf("pipeline : n = %d.\n", pipeline->n);
	lst = pipeline->cmdlines;
	while (lst)
	{
		if (lst->stat == CMDLINE)
			print_cmdline(lst->content, tabs + 1);
		else if (lst->stat == S_PIPE)
		{
			print_tabs(tabs + 1);
			printf("[%s] : (S_PIPE).\n", lst->content);
		}
		lst = lst->next;
	}
}

void print_cmdline(t_cmdline *cmdline, size_t tabs)
{
	if (!cmdline)
	{
		print_tabs(tabs);
		printf("cmdline : (NULL)\n");
		return;
	}
	if (cmdline->node->stat == CMDLINE)
	{
		print_tabs(tabs);
		printf("cmdline :\n");
		print_args(cmdline->node->content, tabs + 1);
		print_reds(cmdline->o_a_i_h, cmdline->words[1], tabs + 1);
	}
	else if (cmdline->node->stat == LISTLINE)
	{
		print_listline(cmdline->node->content, tabs);
		print_reds(cmdline->o_a_i_h, cmdline->words[2], tabs + 1);
	}
}

void print_args(t_cmd_infos *cmd_infos, size_t tabs)
{
	size_t i;

	print_tabs(tabs);
	printf("cmd_path : |%s|\n", cmd_infos->cmd_path);
	print_tabs(tabs);
	printf("cmd_args :\n");
	i = 0;
	while (cmd_infos->cmd_args[i])
	{
		print_tabs(tabs + 1);
		printf("|%s|\n", cmd_infos->cmd_args[i]);
		i++;
	}
	print_tabs(tabs + 1);
	printf("|%s|\n", cmd_infos->cmd_args[i]);
}

void print_reds(int *o_a_i_h, t_list *reds, size_t tabs)
{
	print_tabs(tabs);
	printf("redirections :\n");
	print_list(reds, tabs + 1);
	print_tabs(tabs + 1);
	printf("output : %d\n", o_a_i_h[0]);
	print_tabs(tabs + 1);
	printf("append : %d\n", o_a_i_h[1]);
	print_tabs(tabs + 1);
	printf("input : %d\n", o_a_i_h[2]);
	print_tabs(tabs + 1);
	printf("heredoc : %d\n", o_a_i_h[3]);
}

void print_list(t_list *words, size_t tabs)
{
	if (!words)
	{
		print_tabs(tabs);
		printf("(the list is NULL)\n");
	}
	while (words)
	{
		print_tabs(tabs);
		printf("|%s|", words->content);
		if (words->stat & DR)
			printf(" (D)");
		if (words->stat & SQU)
			printf(" (SQU)");
		if (words->stat & DQU)
			printf(" (DQU)");
		if (words->stat & RD)
		{
			printf(" (R)");
			if (words->stat & RD_OUTPUT)
				printf(" (R_output)");
			else if (words->stat & RD_INPUT)
				printf(" (R_input)");
			else if (words->stat & RD_HEREDOC)
				printf(" (R_heredoc)");
			else if (words->stat & RD_APPEND)
				printf(" (R_append)");
		}
		else if (words->stat & S_RD)
		{
			printf(" (SR)");
			if (words->stat & S_OUTPUT)
				printf(" (R_output)");
			else if (words->stat & S_INPUT)
				printf(" (R_input)");
			else if (words->stat & S_HEREDOC)
				printf(" (R_heredoc)");
			else if (words->stat & S_APPEND)
				printf(" (R_append)");
		}
		else if (words->stat & S_OAP)
		{
			printf(" (SOAP)");
			if (words->stat & S_OR)
				printf(" (S_OR)");
			else if (words->stat & S_AND)
				printf(" (S_AND)");
			else if (words->stat & S_PIPE)
				printf(" (S_PIPE)");
		}
		printf("\n");
		words = words->next;
	}
}

void print_my_env(t_list *env)
{
	char **key_value;

	while (env)
	{
		key_value = env->content;
		printf("key\t->\t%s\n", key_value[0]);
		printf("value\t->\t%s\n\n", key_value[1]);
		env = env->next;
	}
}

void print_tabs(size_t tabs)
{
	while (tabs--)
		printf("\t");
}
