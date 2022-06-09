/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:38:30 by zwina             #+#    #+#             */
/*   Updated: 2021/11/07 16:38:32 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long	i;

	if (dst > src)
	{
		i = len;
		while (--i != -1)
			((char *)dst)[i] = *(char *)(src + i);
	}
	else if (dst < src)
		ft_memcpy(dst, src, len);
	return (dst);
}
