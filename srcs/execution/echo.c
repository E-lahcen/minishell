/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelhlami <lelhlami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:55:09 by lelhlami          #+#    #+#             */
/*   Updated: 2022/06/08 10:38:00 by lelhlami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void echo_func(t_list *line)
{
    if (!ft_strncmp(line->content, "echo", 4))
    {
        while (line->content)
        {
            if (!ft_strncmp(line->next->content, "-n", 2) && line->next->next->content)
                printf("%s", line->next->next->content);
            else if (line->next->content)
                printf("%s\n", line->next->content);
            line->content = line->next->content;
        }
    }
}