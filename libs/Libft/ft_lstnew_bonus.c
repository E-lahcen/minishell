/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:38:17 by zwina             #+#    #+#             */
/*   Updated: 2022/06/05 17:16:10 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, char stat)
{
	t_list	*new_element;

	new_element = (t_list *)malloc(sizeof (t_list));
	if (!new_element)
		return (0);
	new_element->content = content;
	new_element->next = 0;
	new_element->stat = stat;
	return (new_element);
}
