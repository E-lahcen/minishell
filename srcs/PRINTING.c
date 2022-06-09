/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRINTING.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:06:17 by zwina             #+#    #+#             */
/*   Updated: 2022/06/09 11:51:32 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_listline(t_listline *listline)
{
	t_list	*lst;

	if (!listline)
	{
		printf("listline : (NULL)\n");
		return ;
	}
	printf("listline : n = %d.\n", listline->n);
	lst = listline->pipelines;
	while (lst)
	{
		print_pipeline(lst->content);
		lst = lst->next;
	}
}

void	print_pipeline(t_pipeline *pipeline)
{
	t_list	*lst;

	if (!pipeline)
	{
		printf("pipeline : (NULL)\n");
		return ;
	}
	printf("\tpipeline : n = %d, ", pipeline->n);
	if (pipeline->pipestat == POR)
		printf("pipestat = POR.\n");
	else if (pipeline->pipestat == PAND)
		printf("pipestat = PAND.\n");
	else
		printf("pipestat = 0.\n");
	lst = pipeline->cmdlines;
	while (lst)
	{
		print_cmdline(lst->content);
		lst = lst->next;
	}
}

void	print_cmdline(t_cmdline *cmdline)
{
	size_t	i;

	if (!cmdline)
	{
		printf("\t\t--------------------------------\n");
		printf("\t\t(NULL)\n");
		printf("\t\t--------------------------------\n");
		return ;
	}
	printf("\t\t--------------------------------\n");
	if (cmdline->cmd_args)
	{
		printf("\t\tcommand args :\n");
		i = 0;
		while (cmdline->cmd_args[i])
			printf("\t\t\t|%s|\n", cmdline->cmd_args[i++]);
	}
	else
		printf("\t\tcommand args : (NULL)\n");
	if (cmdline->cmd_path)
		printf("\t\tcommand path : |%s|\n", cmdline->cmd_path);
	else
		printf("\t\tcommand path : (NULL)\n");
	printf("\t\toutput : %d\n", cmdline->output);
	printf("\t\tappend : %d\n", cmdline->append);
	printf("\t\tinput : %d\n", cmdline->input);
	printf("\t\theredoc : %d\n", cmdline->heredoc);
	printf("\t\t--------------------------------\n");
}

void	print_list(t_list *words)
{
	if (!words)
		printf("\t\t\t\t(the list is NULL)\n");
	while (words)
	{
		printf("\t\t\t\t|%s|", words->content);
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
