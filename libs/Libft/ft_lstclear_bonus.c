/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:56:51 by zwina             #+#    #+#             */
/*   Updated: 2022/05/30 22:45:18 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (del)
	{
		while (*lst)
		{
			if ((*lst)->content)
				del((*lst)->content);
			next = (*lst)->next;
			free(*lst);
			*lst = next;
		}
	}
}
