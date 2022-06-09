/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:38:03 by zwina             #+#    #+#             */
/*   Updated: 2021/11/10 18:33:35 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)(s + i)) == c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
