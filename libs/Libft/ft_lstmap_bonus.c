/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:09:00 by zwina             #+#    #+#             */
/*   Updated: 2022/05/23 17:35:11 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	new_lst = 0;
	if (f)
	{
		while (lst)
		{
			temp = ft_lstnew(f(lst->content), (char)0);
			if (!temp)
			{
				ft_lstclear(&new_lst, del);
				return (0);
			}
			ft_lstadd_back(&new_lst, temp);
			lst = lst->next;
		}
	}
	return (new_lst);
}
