/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRINTING.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:06:17 by zwina             #+#    #+#             */
/*   Updated: 2022/06/14 08:12:56 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_listline(t_listline *listline, size_t tabs)
{
	t_list	*lst;

	if (!listline)
	{
		print_tabs(tabs);
		printf("listline : (NULL)\n");
		return ;
	}
	print_tabs(tabs);
	printf("listline : n = %d.\n", listline->n);
	lst = listline->pipelines;
	while (lst)
	{
		if (lst->stat == PIPELINE)
			print_pipeline(lst->content, tabs + 1);
		else if (lst->stat == LISTLINE)
			print_listline(lst->content, tabs + 1);
		lst = lst->next;
	}
}

void	print_pipeline(t_pipeline *pipeline, size_t tabs)
{
	t_list	*lst;

	if (!pipeline)
	{
		print_tabs(tabs);
		printf("pipeline : (NULL)\n");
		return ;
	}
	print_tabs(tabs);
	printf("pipeline : n = %d.\n", pipeline->n);
	lst = pipeline->cmdlines;
	while (lst)
	{
		if (lst->stat == CMDLINE)
			print_cmdline(lst->content, tabs + 1);
		else if (lst->stat == LISTLINE)
			print_listline(lst->content, tabs + 1);
		lst = lst->next;
	}
}

void	print_cmdline(t_cmdline *cmdline, size_t tabs)
{
	size_t	i;

	if (!cmdline)
	{
		print_tabs(tabs);
		printf("cmdline : (NULL)\n");
		return ;
	}
	print_tabs(tabs);
	printf("cmdline :\n");
	print_tabs(tabs + 1);
	printf("cmd_path : |%s|\n", cmdline->cmd_path);
	print_tabs(tabs + 1);
	printf("cmd_args :\n");
	i = 0;
	while (cmdline->cmd_args[i])
	{
		print_tabs(tabs + 2);
		printf("|%s|\n", cmdline->cmd_args[i]);
		i++;
	}
	print_tabs(tabs + 1);
	printf("cmd_reds :\n");
	print_list(cmdline->words[1], tabs + 2);
}

void	print_list(t_list *words, size_t tabs)
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

void	print_tabs(size_t tabs)
{
	while (tabs--)
		printf("\t");
}
